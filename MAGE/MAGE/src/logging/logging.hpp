#pragma once

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdio.h>
#include <stdint.h>
#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of logging configurations of the engine processing.
	 */
	struct LoggingConfiguration final {

	public:

		/**
		 Constructs a new logging configuration.
		 */
		LoggingConfiguration() 
			: m_quiet(false), m_verbose(false) {}

		/**
		 Constructs a logging configuration from the given logging configuration.
		 
		 @param[in]		logging_configuration
						A reference to the logging configuration.
		 */
		LoggingConfiguration(const LoggingConfiguration &logging_configuration) 
			: m_quiet(logging_configuration.m_quiet), m_verbose(logging_configuration.m_verbose) {}

		/**
		 Destructs this logging configuration.
		 */
		~LoggingConfiguration() {}

		/**
		 Copies the given logging configuration to this logging configuration.

		 @param[in]		logging_configuration
						A reference to the logging configuration to copy from.
		 @return		A reference to the copy of the given logging configuration
						(i.e. this logging configuration).
		 */
		LoggingConfiguration &operator=(const LoggingConfiguration &logging_configuration) {
			m_quiet   = logging_configuration.m_quiet;
			m_verbose = logging_configuration.m_verbose;
			return (*this);
		}

		/**
		 Checks whether the logging of the engine processing is quiet.

		 @return		@c true if the logging of the engine processing is quiet.
						@c false otherwise.
		 */
		bool IsQuiet() const {
			return m_quiet;
		}

		/**
		 Checks wheter the logging of the engine processing is verbose.

		 @return		@c true if the logging of the engine processing is verbose.
						@c false otherwise.
		 */
		bool IsVerbose() const {
			return m_verbose;
		}

	private:

		/**
		 Flag indicating the logging of the engine processing is quiet.
		 */
		bool m_quiet;

		/**
		 Flag indicating the logging of the engine processing is verbose.
		 */
		bool m_verbose;
	};

	/**
	 The logging configuration defined by the user and used by the engine.
	 */
	extern LoggingConfiguration g_logging_configuration;

	/**
	 Returns the fixed console width.

	 @return		The fixed console width.
	 */
	uint16_t ConsoleWidth();

	/**
	 Allocates a console to this engine for basic io and
	 redirects stdin, stdout and stderr to the allocated console.

	 @return		A success/error value.
	 */
	HRESULT InitializeConsole();
}