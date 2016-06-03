//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "BsModule.h"
#include "BsVector3.h"

namespace BansheeEngine
{
	/** @addtogroup Audio
	 *  @{
	 */

	/** Identifier for a device that can be used for playing audio. */
	struct AudioDevice
	{
		WString name;
	};

	/** Provides global functionality relating to sounds and music. */
	class BS_CORE_EXPORT Audio : public Module<Audio>
	{
	public:
		virtual ~Audio() {}

		/** 
		 * Starts playback of the provided audio clip. This can be used for a quicker way of creating audio sources if you
		 * don't need the full control provided by creating AudioSource manually.
		 *
		 * @param[in]	clip		Audio clip to play.
		 * @param[in]	position	Position in world space to play the clip at. Only relevant if the clip is 3D.
		 * @param[in]	volume		Volume to play the clip at.
		 */
		void play(const HAudioClip& clip, const Vector3& position = Vector3::ZERO, float volume = 1.0f);

		/** Sets global audio volume. In range [0, 1]. */
		virtual void setVolume(float volume) = 0;

		/** Returns global audio volume. In range [0, 1]. */
		virtual float getVolume() const = 0;

		/** Pauses audio reproduction globally. */
		virtual void setPaused(bool paused) = 0;

		/** Checks is audio reproduction currently paused. */
		virtual bool isPaused() const = 0;

		/** Changes the device on which is the audio played back on. */
		virtual void setActiveDevice(const AudioDevice& device) = 0;

		/** Retrieves the identifier of the device that the audio is currently being played back on. */
		virtual AudioDevice getActiveDevice() const = 0;
		
		/** Returns the default audio device identifier. */
		virtual AudioDevice getDefaultDevice() const = 0;

		/** Returns a list of all available audio devices. */
		virtual const Vector<AudioDevice>& getAllDevices() const = 0;

		/** @name Internal
		 *  @{
		 */

		/** Called once per frame. Queues streaming audio requests. */
		virtual void _update();

		/** @} */
	protected:
		friend class AudioClip;
		friend class AudioListener;
		friend class AudioSource;

		/** 
		 * Creates a new audio clip.
		 *
		 * @param[in]	samples		Stream containing audio samples in format specified in @p desc.
		 * @param[in]	streamSize	Size of the audio data in the provided stream, in bytes.
		 * @param[in]	numSamples	Number of samples in @p samples stream.
		 * @param[in]	desc		Descriptor describing the type of the audio stream (format, sample rate, etc.).
		 * @return					Newly created AudioClip. Must be manually initialized.
		 */
		virtual SPtr<AudioClip> createClip(const SPtr<DataStream>& samples, UINT32 streamSize, UINT32 numSamples,
			const AUDIO_CLIP_DESC& desc) = 0;

		/** Creates a new AudioListener. */
		virtual SPtr<AudioListener> createListener() = 0;

		/** Creates a new AudioSource. */
		virtual SPtr<AudioSource> createSource() = 0;

		/** Stops playback of all sources started with Audio::play calls. */
		void stopManualSources();

	private:
		Vector<SPtr<AudioSource>> mManualSources;
		Vector<SPtr<AudioSource>> mTempSources;
	};

	/** Provides easier access to Audio. */
	BS_CORE_EXPORT Audio& gAudio();

	/** @} */
}