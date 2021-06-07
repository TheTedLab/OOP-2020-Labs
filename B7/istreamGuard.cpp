#include "istreamGuard.hpp"

IstreamGuard::IstreamGuard(std::istream& sin) :
  sin_(sin),
  flags_(sin.flags())
{}

IstreamGuard::~IstreamGuard()
{
  sin_.flags(flags_);
}
