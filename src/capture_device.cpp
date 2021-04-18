#include "capture_device.hpp"

#include <pcap/pcap.h>
#include <string>

/**
 * Opens a pcap device.
 * 
 * @return Error/return code.
 */
enum CaptureDevice::ErrorCode CaptureDevice::open_device(const std::string device_name, bool promiscuous_mode)
{
    int rc = 0;
    char errbuf[PCAP_ERRBUF_SIZE];
    errbuf[0] = '\0';

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
        this->pcap_ctx.reset();
        return CaptureDevice::ErrorCode::PermissionDenied;
    }
    else if (rc == PCAP_ERROR_NO_SUCH_DEVICE)
    {
        this->pcap_ctx.reset();
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

/**
 * Getter for accessing the pcap_t context
 * 
 * @return A unique pointer reference for accessing the pcap_t context.
 */
std::unique_ptr<pcap_t, CaptureDevice::pcap_ctx_deleter>& CaptureDevice::get_ctx()
{
    return this->pcap_ctx;
}

/*void CaptureDevice::close_device()
{
    this->pcap_ctx.reset();
}*/
