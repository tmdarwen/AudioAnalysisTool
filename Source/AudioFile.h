#include <Singleton.h>
#include <WaveFile/WaveFileReader.h>
#include <Signal/TransientDetector.h>
#include <memory>

class AudioFile : public Singleton<AudioFile>
{
	public:
		void Initialize(const std::string& waveFileName);

		bool FileLoaded();  // Returns true if an audio file is loaded, false otherwise

		std::shared_ptr<WaveFile::WaveFileReader> GetWaveFile();

		const std::vector<double>& GetAudioData();

		// Transient Methods
		std::shared_ptr<Signal::TransientDetector> GetTransientDetector();
		std::size_t GetTransientCount();
		std::size_t GetTransient(std::size_t transientNumber);
		const std::vector<std::size_t> GetTransients() const;
		void RefreshTransients();

	private:
		std::string waveFileName_;
		std::shared_ptr<WaveFile::WaveFileReader> waveFileReader_;
		std::vector<double> audioData_;

		std::shared_ptr<Signal::TransientDetector> transientDetector_;
		std::vector<std::size_t> transients_;

	friend Singleton<AudioFile>;
};

