#ifndef LOGGING_H
#define LOGGING_H

#include <boost/log/expressions.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

/**
 * Use these conventions when logging:
 * https://stackoverflow.com/questions/2031163/when-to-use-the-different-log-levels
 */
#define TRACE BOOST_LOG_SEV(smpp_lib_logger::get(), boost::log::trivial::trace)
#define DEBUG BOOST_LOG_SEV(smpp_lib_logger::get(), boost::log::trivial::debug)
#define INFO BOOST_LOG_SEV(smpp_lib_logger::get(), boost::log::trivial::info)
#define WARN BOOST_LOG_SEV(smpp_lib_logger::get(), boost::log::trivial::warning)
#define ERROR BOOST_LOG_SEV(smpp_lib_logger::get(), boost::log::trivial::error)
#define FATAL BOOST_LOG_SEV(smpp_lib_logger::get(), boost::log::trivial::fatal)

const std::string LOG_FILE = "smpp_lib.log";

// Narrow-char thread-safe logger.
using logger_t = boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>;

// declares a global logger with a custom initialization
BOOST_LOG_GLOBAL_LOGGER(smpp_lib_logger, logger_t)

#endif