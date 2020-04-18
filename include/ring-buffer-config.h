#ifndef _RING_BUFFER_CONFIG_H
#define _RING_BUFFER_CONFIG_H

#ifdef RING_BUFFER_NOEXCEPT
#define NOEXCEPT noexcept
#define COND_NOEXCEPT(x) noexcept(x)
#else
#define NOEXCEPT
#define COND_NOEXCEPT(x)
#endif

#ifdef RING_BUFFER_CONSTEXPR
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif

#ifdef RING_BUFFER_CONSTEXPR_DESTRUCTORS
#define CONSTEXPR_D CONSTEXPR
#else
#define CONSTEXPR_D
#endif

#endif
