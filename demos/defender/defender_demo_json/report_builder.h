/*
 * AWS IoT Device SDK for Embedded C 202412.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef REPORT_BUILDER_H_
#define REPORT_BUILDER_H_

/* Standard includes. */
#include <stdlib.h>

/* Metrics collector. */
#include "metrics_collector.h"

/**
 * @brief Return codes from report builder APIs.
 */
typedef enum
{
    ReportBuilderSuccess = 0,
    ReportBuilderBadParameter,
    ReportBuilderBufferTooSmall
} ReportBuilderStatus_t;

/**
 * @brief Represents the set of custom metrics to send to AWS IoT Device Defender service.
 *
 * This demo shows how various system metrics can be sent as custom metrics to
 * AWS IoT Device Defender service.
 *
 * For more information on custom metrics, refer to the following AWS document:
 * https://docs.aws.amazon.com/iot/latest/developerguide/dd-detect-custom-metrics.html
 */
typedef struct CustomMetrics
{
    /* System uptime. */
    uint64_t uptime;
    /* System free memory. */
    uint64_t memFree;
    /* Userspace usage of each CPU. */
    uint64_t * pCpuUserUsage;
    /* Length of pCpuUserUsage. */
    size_t cpuCount;

    /* Names of the network interfaces.
     * These have max length 15 on Linux, not including trailing null. */
    char ( *pNetworkInterfaceNames )[ 16 ];
    /* Addresses of the network interfaces. */
    uint32_t * pNetworkInterfaceAddresses;
    /* Length of network_interface_names and network_interface_addresses. */
    size_t networkInterfaceCount;
} CustomMetrics_t;

/**
 * @brief Represents metrics to be included in the report.
 */
typedef struct ReportMetrics
{
    NetworkStats_t * pNetworkStats;
    uint16_t * pOpenTcpPortsArray;
    uint32_t openTcpPortsArrayLength;
    uint16_t * pOpenUdpPortsArray;
    uint32_t openUdpPortsArrayLength;
    Connection_t * pEstablishedConnectionsArray;
    uint32_t establishedConnectionsArrayLength;
    CustomMetrics_t customMetrics;
} ReportMetrics_t;

/**
 * @brief Generate a report in the format expected by the AWS IoT Device Defender
 * Service.
 *
 * @param[in] pBuffer The buffer to write the report into.
 * @param[in] bufferLength The length of the buffer.
 * @param[in] pMetrics Metrics to write in the generated report.
 * @param[in] majorReportVersion Major version of the report.
 * @param[in] minorReportVersion Minor version of the report.
 * @param[in] reportId Value to be used as the reportId in the generated report.
 * @param[out] pOutReportLength The length of the generated report.
 *
 * @return #ReportBuilderSuccess if the report is successfully generated;
 * #ReportBuilderBadParameter if invalid parameters are passed;
 * #ReportBuilderBufferTooSmall if the buffer cannot hold the full report.
 */
ReportBuilderStatus_t GenerateJsonReport( char * pBuffer,
                                          uint32_t bufferLength,
                                          const ReportMetrics_t * pMetrics,
                                          uint32_t majorReportVersion,
                                          uint32_t minorReportVersion,
                                          uint32_t reportId,
                                          uint32_t * pOutReportLength );

#endif /* ifndef REPORT_BUILDER_H_ */
