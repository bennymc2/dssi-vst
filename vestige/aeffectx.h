/*
 * aeffectx.h - simple header to allow VeSTige compilation and eventually work
 *
 * Copyright (c) 2006 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */
#include <stdint.h>
#ifndef _AEFFECTX_H
#define _AEFFECTX_H

#define CCONST(a, b, c, d)( ( ( (int) a ) << 24 ) |		\
				( ( (int) b ) << 16 ) |		\
				( ( (int) c ) << 8 ) |		\
				( ( (int) d ) << 0 ) )

#define audioMasterAutomate 0
#define audioMasterVersion 1
#define audioMasterCurrentId 2
#define audioMasterIdle 3
#define audioMasterPinConnected 4
// unsupported? 5
#define audioMasterWantMidi 6
#define audioMasterGetTime 7
#define audioMasterProcessEvents 8
#define audioMasterSetTime 9
#define audioMasterTempoAt 10
#define audioMasterGetNumAutomatableParameters 11
#define audioMasterGetParameterQuantization 12
#define audioMasterIOChanged 13
#define audioMasterNeedIdle 14
#define audioMasterSizeWindow 15
#define audioMasterGetSampleRate 16
#define audioMasterGetBlockSize 17
#define audioMasterGetInputLatency 18
#define audioMasterGetOutputLatency 19
#define audioMasterGetPreviousPlug 20
#define audioMasterGetNextPlug 21
#define audioMasterWillReplaceOrAccumulate 22
#define audioMasterGetCurrentProcessLevel 23
#define audioMasterGetAutomationState 24
#define audioMasterOfflineStart 25
#define audioMasterOfflineRead 26
#define audioMasterOfflineWrite 27
#define audioMasterOfflineGetCurrentPass 28
#define audioMasterOfflineGetCurrentMetaPass 29
#define audioMasterSetOutputSampleRate 30
// unsupported? 31
#define audioMasterGetSpeakerArrangement 31 // deprecated in 2.4?
#define audioMasterGetVendorString 32
#define audioMasterGetProductString 33
#define audioMasterGetVendorVersion 34
#define audioMasterVendorSpecific 35
#define audioMasterSetIcon 36
#define audioMasterCanDo 37
#define audioMasterGetLanguage 38
#define audioMasterOpenWindow 39
#define audioMasterCloseWindow 40
#define audioMasterGetDirectory 41
#define audioMasterUpdateDisplay 42
#define audioMasterBeginEdit 43
#define audioMasterEndEdit 44
#define audioMasterOpenFileSelector 45
#define audioMasterCloseFileSelector 46 // currently unused
#define audioMasterEditFile 47 // currently unused
#define audioMasterGetChunkFile 48 // currently unused
#define audioMasterGetInputSpeakerArrangement 49 // currently unused

#define effFlagsHasEditor 1
#define effFlagsCanReplacing (1 << 4) // very likely
#define effFlagsIsSynth (1 << 8) // currently unused

#define effOpen 0
#define effClose 1 // currently unused
#define effSetProgram 2 // currently unused
#define effGetProgram 3 // currently unused
#define effGetProgramName 5 // currently unused
#define effGetParamName 8 // currently unused
#define effSetSampleRate 10
#define effSetBlockSize 11
#define effMainsChanged 12
#define effEditGetRect 13
#define effEditOpen 14
#define effEditClose 15
#define effEditIdle 19
#define effEditTop 20
#define effProcessEvents 25
#define effGetEffectName 45
#define effGetVendorString 47
#define effGetProductString 48
#define effGetVendorVersion 49
#define effCanDo 51 // currently unused
/* from http://asseca.com/vst-24-specs/efGetParameterProperties.html */
#define effGetParameterProperties 56
#define effGetVstVersion 58 // currently unused

#define kEffectMagic (CCONST( 'V', 's', 't', 'P' ))
#define kVstLangEnglish 1
#define kVstMidiType 1
#define kVstTempoValid (1 << 10)
#define kVstTransportPlaying (1 << 1)


struct RemoteVstPlugin;

#define kVstNanosValid (1 << 8)
#define kVstPpqPosValid (1 << 9)
#define kVstTempoValid (1 << 10)
#define kVstBarsValid (1 << 11)
#define kVstCyclePosValid (1 << 12)
#define kVstTimeSigValid (1 << 13)
#define kVstSmpteValid (1 << 14)
#define kVstClockValid (1 << 15)

struct _VstMidiEvent
{
	// 00
	int type;
	// 04
	int byteSize;
	// 08
	int deltaFrames;
	// 0c?
	int flags;
	// 10?
	int noteLength;
	// 14?
	int noteOffset;
	// 18
	char midiData[4];
	// 1c?
	char detune;
	// 1d?
	char noteOffVelocity;
	// 1e?
	char reserved1;
	// 1f?
	char reserved2;
};

typedef struct _VstMidiEvent VstMidiEvent;


struct _VstEvent
{
	char dump[sizeof (VstMidiEvent)];

};

typedef struct _VstEvent VstEvent;

struct _VstEvents
{
	// 00
	int numEvents;
	// 04
	void *reserved;
	// 08
	VstEvent * events[];
};

typedef struct _VstEvents VstEvents;

/* this struct taken from http://asseca.com/vst-24-specs/efGetParameterProperties.html */
struct _VstParameterProperties
{
	float stepFloat;
	float smallStepFloat;
	float largeStepFloat;
	char label[64];
	int32_t flags;
	int32_t minInteger;
	int32_t maxInteger;
	int32_t stepInteger;
	int32_t largeStepInteger;
	char shortLabel[8];
};

typedef struct _VstParameterProperties VstParameterProperties;

/* this enum taken from http://asseca.com/vst-24-specs/efGetParameterProperties.html */
enum VstParameterFlags
{
	kVstParameterIsSwitch                = 1 << 0,  /* parameter is a switch (on/off) */
	kVstParameterUsesIntegerMinMax       = 1 << 1,  /* minInteger, maxInteger valid */
	kVstParameterUsesFloatStep           = 1 << 2,  /* stepFloat, smallStepFloat, largeStepFloat valid */
	kVstParameterUsesIntStep             = 1 << 3,  /* stepInteger, largeStepInteger valid */
	kVstParameterSupportsDisplayIndex    = 1 << 4,  /* displayIndex valid */
	kVstParameterSupportsDisplayCategory = 1 << 5,  /* category, etc. valid */
	kVstParameterCanRamp                 = 1 << 6   /* set if parameter value can ramp up/down */
};

struct _AEffect
{
	// Never use virtual functions!!!
	// 00-03
	int magic;
	// dispatcher 04-07
	intptr_t (* dispatcher) (struct _AEffect *, int, int, intptr_t, void *, float);
	// process, quite sure 08-0b
	void (* process) (struct _AEffect *, float **, float **, int);
	// setParameter 0c-0f
	void (* setParameter) (struct _AEffect *, int, float);
	// getParameter 10-13
	float (* getParameter) (struct _AEffect *, int);
	// programs 14-17
	int numPrograms;
	// Params 18-1b
	int numParams;
	// Input 1c-1f
	int numInputs;
	// Output 20-23
	int numOutputs;
	// flags 24-27
	int flags;
	// Fill somewhere 28-2b
	void *ptr1;
	void *ptr2;
	// Zeroes 2c-2f 30-33 34-37 38-3b
	char empty3[4 + 4 + 4];
	// 1.0f 3c-3f
	float unkown_float;
	// An object? pointer 40-43
	void *ptr3;
	// Zeroes 44-47
	void *user;
	// Id 48-4b
	int32_t uniqueID;
	// Don't know 4c-4f
	char unknown1[4];
	// processReplacing 50-53
	void (* processReplacing) (struct _AEffect *, float **, float **, int);
};

typedef struct _AEffect AEffect;

struct _VstTimeInfo
{
	// 00
	double samplePos;
	// 08
	double sampleRate;
	// unconfirmed 10 18
	char empty1[8 + 8];
	// 20?
	double tempo;
	// unconfirmed 28 30 38
	char empty2[8 + 8 + 8];
	// 40?
	int timeSigNumerator;
	// 44?
	int timeSigDenominator;
	// unconfirmed 48 4c 50
	char empty3[4 + 4 + 4];
	// 54
	int flags;
};

typedef struct _VstTimeInfo VstTimeInfo;

typedef intptr_t (* audioMasterCallback) (AEffect *, int32_t, int32_t, intptr_t, void *, float);

#endif
