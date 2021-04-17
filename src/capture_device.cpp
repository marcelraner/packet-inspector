#include "capture_device.hpp"

#include "logging.hpp"

#include <pcap/pcap.h>
#include <string>

enum CaptureDevice::ErrorCode CaptureDevice::open_device(const std::string device_name, bool promiscuous_mode)
{
    int rc = 0;
    char errbuf[PCAP_ERRBUF_SIZE];
    errbuf[0] = '\0';

    TRACE("pcap_create");
    this->pcap_ctx.reset(pcap_create(device_name.c_str(), errbuf));
    if (this->pcap_ctx.get() == NULL) {
        std::string error_message = "pcap_create() returned NULL (errbuf: " + 
                                    std::string(errbuf) + ")";
        throw std::runtime_error(error_message);
    }

    rc = pcap_set_timeout(this->pcap_ctx.get(), 1000);
    if (rc != 0) {
        std::string error_message = "pcap_set_timeout() returned " + 
                                    std::to_string(rc);
        throw std::runtime_error(error_message);
    }
    rc = pcap_set_promisc(this->pcap_ctx.get(), promiscuous_mode ? 1 : 0);
    if (rc != 0) {
        std::string error_message = "pcap_set_promisc() returned " + 
                                    std::to_string(rc);
        throw std::runtime_error(error_message);
    }

    rc = pcap_activate(this->pcap_ctx.get());
    if (rc == PCAP_ERROR_PERM_DENIED)
    {
        this->close_device();
        return CaptureDevice::ErrorCode::PermissionDenied;
    }
    else if (rc == PCAP_ERROR_NO_SUCH_DEVICE)
    {
        this->close_device();
        return CaptureDevice::ErrorCode::NoSuchDevice;
    }
    else if (rc != 0) {
        std::string error_message = "pcap_activate() returned " + 
                                    std::to_string(rc);
        throw std::runtime_error(error_message);
    }

    if (pcap_datalink(this->pcap_ctx.get()) != DLT_EN10MB)
    {
        throw std::runtime_error("DLT_EN10MB is not supported");
    }

    return CaptureDevice::ErrorCode::Ok;
}

void CaptureDevice::close_device()
{
    this->pcap_ctx.reset();
}
