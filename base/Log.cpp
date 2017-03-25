#include <string.h>
#include <errno.h>
#include <iostream>
#include <limits.h>

#include <Log.h>

const char *fas::Log::CLRF = "\r\n";
fas::Log::Log() :
  runTimeLevel_(Log::LogLevel()),
  file_(""),
  line_(INT_MAX),
  func_(""),
  abort_(false),
  output_(defaultLogOutput),
  buffer_() {
}

fas::Log::Log(std::string file, int line) :
  runTimeLevel_(Log::LogLevel()),
  file_(file),
  line_(line),
  func_(""),
  abort_(false),
  output_(defaultLogOutput),
  buffer_() {
  buffer_ << file_ << " " << line_ << " ";
}

fas::Log::Log(std::string file, int line, Log::LogLevel level) :
  runTimeLevel_(level),
  file_(file),
  line_(line),
  func_(""),
  abort_(false),
  output_(defaultLogOutput),
  buffer_() {
  buffer_ << file_ << " " << line_ << " ";
}

fas::Log::Log(std::string file, int line, Log::LogLevel level, std::string func) :
  runTimeLevel_(level),
  file_(file),
  line_(line),
  func_(func),
  abort_(false),
  output_(defaultLogOutput),
  buffer_() {
  buffer_ << file_ << " " << line_ << " " << func_  << " ";
}

fas::Log::Log(std::string file, int line, bool toAbort) :
  runTimeLevel_(Log::LogLevel()),
  file_(file),
  line_(line),
  func_(""),
  abort_(toAbort),
  output_(fas::defaultLogOutput),
  buffer_(){
  buffer_ << file_ << " " << line_ << " ";
}

fas::Log& fas::Log::fflush() {
  if (!output_) {
    assert(false);
  }
  if (runTimeLevel_ >= Log::LogLevel()) {
    output_(buffer_.str().c_str(), buffer_.str().size());
  }
  buffer_.str("");
  return *this;
}

fas::Log::LogLevel fas::Log::logLevel() {
  return Log::LogLevel::TRACE;
}

std::ostringstream& fas::Log::getBuffer() {
  return buffer_;
}

void fas::Log::setOutput(default_output_t output) {
  output_ = output;
}

fas::Log::~Log() {
  fflush();
  if (abort_) {
    ::abort();
  }
}

bool fas::defaultLogOutput(const char* data, int len) {
  int ret = ::write(STDOUT_FILENO, data, len);
  if (ret == -1) {
    LOGGER_SYSERR << "write error : " << strerror(errno) << Log::CLRF;
    return false;
  }
  return true;
}

fas::Log& fas::Log::LOG() {
  return *this;
}

void fas::Logger(std::string file, int line, std::string msg) {
  Log log;
  log << file << " " << line << " " << msg << Log::CLRF;
  log.fflush();
}

void fas::Logger(std::string file, int line, Log::LogLevel level, std::string msg) {
  Log log;
  log << file << " " << line << " " <<  level << " " << msg << Log::CLRF;
  log.fflush();
}

void fas::Logger(std::string file, int line, Log::LogLevel level, std::string func, std::string msg) {
  Log log;
  log << file << " " << line << " " <<  level << " " << func << " " << msg << Log::CLRF;
  log.fflush();
}

void fas::Logger(std::string file, int line, bool toAbort, std::string msg) {
  Log log;
  log << file << " " << line << " " << msg << Log::CLRF;
  log.fflush();

  if (toAbort) {
    ::abort();
  }
}

