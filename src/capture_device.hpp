#ifndef CAPTURE_DEVICE_HPP
#define CAPTURE_DEVICE_HPP

#include <pcap/pcap.h>
#include <string>
#include <memory>
#include <iostream>

class PaketReader;

class CaptureDevice
{
private:
    struct pcap_ctx_deleter {
        void operator()(pcap_t* ptr) {
            pcap_close(ptr);
        }
    };
public:
    enum ErrorCode {
        Ok,
        PermissionDenied,
        NoSuchDevice
    };
public:
    std::unique_ptr<pcap_t, pcap_ctx_deleter> pcap_ctx;
public:
    enum ErrorCode open_device(const std::string, bool);
    void close_device();
};

#endif // CAPTURE_DEVICE_HPP
