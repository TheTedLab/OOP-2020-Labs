#ifndef ISTREAM_GUARD_HPP
#define ISTREAM_GUARD_HPP

#include <istream>

class IstreamGuard
{
public:
  explicit IstreamGuard(std::istream & sin);
  ~IstreamGuard();
private:
  std::istream & sin_;
  std::ios_base::fmtflags flags_;
};

#endif
