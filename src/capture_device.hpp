#ifndef CAPTURE_DEVICE_HPP
#define CAPTURE_DEVICE_HPP

#include <pcap/pcap.h>
#include <string>
#include <memory>
#include <iostream>

/**
 * Representation of a pcap device
 *
 * Objects of this class enables you to open a pcap context for a chosen
 * network interface. You can access the pcap context via the get_ctx() method.
 */
class CaptureDevice
{
private:
    struct pcap_ctx_deleter {
        void operator()(pcap_t* ptr) {
            pcap_close(ptr);
        }
    };
    std::unique_ptr<pcap_t, pcap_ctx_deleter> pcap_ctx;
public:
    /** Specifies return values for methods form class CaptureDevice */ 
    enum ErrorCode {
        Ok,
        PermissionDenied,
        NoSuchDevice
    };
    enum ErrorCode open_device(const std::string, bool);
    //void close_device();
    std::unique_ptr<pcap_t, pcap_ctx_deleter>& get_ctx();
};

#endif // CAPTURE_DEVICE_HPP
