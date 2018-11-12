/* =================================================================================================

(c - MIT) T.W.J. de Geus (Tom) | www.geus.me | github.com/tdegeus/GMatElastoPlasticQPot

================================================================================================= */

#ifndef GMATELASTOPLASTICQPOT_CARTESIAN2D_ELASTIC_HPP
#define GMATELASTOPLASTICQPOT_CARTESIAN2D_ELASTIC_HPP

// -------------------------------------------------------------------------------------------------

#include "GMatElastoPlasticQPot.h"

// =================================================================================================

namespace GMatElastoPlasticQPot {
namespace Cartesian2d {

// -------------------------------------------------------------------------------------------------

inline Elastic::Elastic(double K, double G) : m_K(K), m_G(G)
{
}

// -------------------------------------------------------------------------------------------------

inline double Elastic::epsd(const T2s &Eps) const
{
  auto Epsd = Eps - 0.5 * trace(Eps) * eye();

  return std::sqrt(.5*ddot(Epsd,Epsd));
}

// -------------------------------------------------------------------------------------------------

inline double Elastic::epsp(const T2s &) const
{
  return 0.0;
}

// -------------------------------------------------------------------------------------------------

inline double Elastic::epsp(double) const
{
  return 0.0;
}

// -------------------------------------------------------------------------------------------------

inline double Elastic::epsy(size_t) const
{
  return std::numeric_limits<double>::infinity();
}

// -------------------------------------------------------------------------------------------------

inline size_t Elastic::find(const T2s &) const
{
  return 0;
}

// -------------------------------------------------------------------------------------------------

inline size_t Elastic::find(double) const
{
  return 0;
}

// -------------------------------------------------------------------------------------------------

inline T2s Elastic::Sig(const T2s &Eps) const
{
  // decompose strain: hydrostatic part, deviatoric part
  T2s  I    = eye();
  auto epsm = 0.5 * trace(Eps);
  auto Epsd = Eps - epsm * I;

  // return stress tensor
  return m_K * epsm * I + m_G * Epsd;
}

// -------------------------------------------------------------------------------------------------

inline double Elastic::energy(const T2s &Eps) const
{
  // decompose strain: hydrostatic part, deviatoric part
  T2s  I    = eye();
  auto epsm = 0.5 * trace(Eps);
  auto Epsd = Eps - epsm * I;
  auto epsd = std::sqrt(.5*ddot(Epsd,Epsd));

  // hydrostatic part of the energy
  auto U = m_K * std::pow(epsm,2.);
  // deviatoric part of the energy
  auto V = m_G * std::pow(epsd,2.);

  // return total energy
  return U + V;
}

// =================================================================================================

}} // namespace ...

// =================================================================================================

#endif