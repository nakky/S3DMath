/******************************************************************/
/*!
	@file	MathematicSystem.h
	@brief	Mathematic processor
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 30, 2020
*/
/******************************************************************/

#ifndef S3DMATH_MATHEMATICSYSTEM_H
#define S3DMATH_MATHEMATICSYSTEM_H

#include "S3DMath/Common.h"
#include "S3DMath/CPU.h"

namespace S3DMath
{

	enum SIMDInstructionType
	{
		SIMD_NONE = 0,
#if defined SIMDARCH_SSE
		SIMD_SSE,
		SIMD_VMX,
		SIMD_VMX128,
#elif defined SIMDARCH_NEON
		SIMD_NEON,
#endif
	};

	//////////////////////////////////////////////////////
	//				forward declarations				//
	//////////////////////////////////////////////////////
	// implemented
	class MathematicSystem;

	// required
	class Matrix44;

	//////////////////////////////////////////////////////
	//				class declarations					//
	//////////////////////////////////////////////////////
	/****************************************/
	/*!
	 @class	MathematicSystem
	 @brief
	 @note
	 @author	Naoto Nakamura
	 @date	Apl. 1, 2009
	 */
	/****************************************/
	class MathematicSystem
	{
		friend class Quaternion4;
		friend class Matrix44;

	private:
		MathematicSystem() {}

	public:
		static void init();
		static void cleanup();

		static void setSIMDInstructionType(const SIMDInstructionType type);

		static SIMDInstructionType getSIMDInstructionType() { return mSIMDInstructionType; }

	private:
		static CPU mCPU;

		static SIMDInstructionType mSIMDInstructionType;
	};

}; // namespace S3DMath

#endif // S3DMATH_MATHEMATICSYSTEM_H
