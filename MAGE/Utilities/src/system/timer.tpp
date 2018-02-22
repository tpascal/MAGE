#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ClockT >
	Timer< ClockT >::Timer() noexcept
		: m_clock(),
		m_last_timestamp(TimeStamp::min()),
		m_delta_time(TimeInterval::min()),
		m_total_delta_time(TimeInterval::min()),
		m_running(false) {}

	template< typename ClockT >
	inline void Timer< ClockT >::Start() noexcept {
		if (m_running) {
			return;
		}

		m_running = true;
		ResetDeltaTime();
	}

	template< typename ClockT >
	inline void Timer< ClockT >::Stop() noexcept {
		if (!m_running) {
			return;
		}

		m_running = false;
		UpdateDeltaTime();
	}

	template< typename ClockT >
	inline void Timer< ClockT >::Restart() noexcept {
		m_running = false;
		Start();
	}

	template< typename ClockT >
	inline void Timer< ClockT >::Resume() noexcept {
		if (m_running) {
			return;
		}

		m_running = true;
		m_last_timestamp = m_clock.now();
	}

	template< typename ClockT >
	inline F64 Timer< ClockT >::GetDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		using Seconds = std::chrono::duration< F64 >;
		return std::chrono::duration_cast< Seconds >(m_delta_time).count();
	}

	template< typename ClockT >
	inline F64 Timer< ClockT >::GetTotalDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		using Seconds = std::chrono::duration< F64 >;
		return std::chrono::duration_cast< Seconds >(m_total_delta_time).count();
	}

	template< typename ClockT >
	inline void Timer< ClockT >::ResetDeltaTime() const noexcept {
		// Resets the delta time of this timer.
		m_delta_time       = TimeInterval::min();
		// Resets the total delta time of this timer.
		m_total_delta_time = TimeInterval::min();
		// Resets the last timestamp of this timer.
		m_last_timestamp   = m_clock.now();
	}

	template< typename ClockT >
	inline void Timer< ClockT >::UpdateDeltaTime() const noexcept {
		// Get the current timestamp of this timer.
		const auto current_timestamp = m_clock.now();

		// Updates the delta time of this timer.
		m_delta_time        = current_timestamp - m_last_timestamp;
		// Updates the total delta time of this timer.
		m_total_delta_time += m_delta_time;
		// Updates the last timestamp of this timer.
		m_last_timestamp    = current_timestamp;
	}
}