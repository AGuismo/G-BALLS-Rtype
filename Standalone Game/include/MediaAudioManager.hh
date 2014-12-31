#ifndef MEDIA_AUDIO_MANAGER_H_
# define MEDIA_AUDIO_MANAGER_H_

# include	<exception>
# include	<map>
# include	<string>

class	Sound;

class	MediaAudioManager
{
  typedef std::map<std::string, Sound *>	Sound_type;
private:
  MediaAudioManager(void);
  virtual ~MediaAudioManager(void);

public:
  static MediaAudioManager	&getInstance(void);

public:
  void			addSound(const std::string &name, const std::string &path);
  void			addSound(const std::string &, Sound *);
  void			delSound(const std::string &);
  Sound			*getSound(const std::string &);

private:
  MediaAudioManager(MediaAudioManager const&);
  MediaAudioManager& operator=(MediaAudioManager const&);

private:
  Sound_type	_lnkSound;

public:
  class Exception
  {
  public:
    Exception(const std::string &msg) throw();
    virtual ~Exception() throw();

  public:
    Exception(Exception const&) throw();
    Exception& operator=(Exception const&) throw();

  public:
    virtual const char	*what() const throw();

  private:
    std::string		_what;
  };
};

#endif /* MEDIA_AUDIO_MANAGER_H_ */
