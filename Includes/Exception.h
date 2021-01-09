#pragma once

#include <string>
#include <stdexcept>

#define LOCKDOWNSSL_ASSERT(exp, exc) if(!(exp)) throw exc

namespace LockdownSSL
{
	namespace Exceptions
	{
		class Exception : public std::runtime_error
		{
		public:
			enum ErrorType
			{
				DATA_INTEGRITY_CHECK_FAILED,
				INVALID_DATA_FORMAT,
			};

			virtual ~Exception() throw() {}

			explicit Exception(ErrorType errorType, const std::string& s) : std::runtime_error("LockdownSSLException: " + s), errType(errorType){}

			ErrorType GetErrorType() const { return errType; }

		private:
			ErrorType errType;
		};

		class InvalidDataFormatException : public Exception
		{
		public:
			explicit InvalidDataFormatException(const std::string& s) : Exception(INVALID_DATA_FORMAT, s + " (InvalidDataFormatException)") {}
		};

		class IntegrityCheckException : public Exception
		{
		public:
			explicit IntegrityCheckException(const std::string& s) : Exception(DATA_INTEGRITY_CHECK_FAILED, s + " (IntegrityCheckException)") {}
		};
	}
}