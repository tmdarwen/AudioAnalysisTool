#include <Singleton.h>
#include <WaveFile/WaveFileReader.h>
#include <memory>

class AudioFile : public Singleton<AudioFile>
{
	public:
		void Initialize(const std::string& waveFileName);
		std::shared_ptr<WaveFile::WaveFileReader> GetWaveFile();

		const std::vector<double>& GetAudioData();

	private:
		std::string waveFileName_;
		std::shared_ptr<WaveFile::WaveFileReader> waveFileReader_;

		std::vector<double> audioData_;

	friend Singleton<AudioFile>;
};

