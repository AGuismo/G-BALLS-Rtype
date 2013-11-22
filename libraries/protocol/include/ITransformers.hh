#ifndef ITRANSFORMERS_H_
# define ITRANFORMERS_H_

class	Protocol;
class	ARequest;

class ITransformers
{
public:
  virtual ~ITransformers() {};

public:
  virtual ARequest	*clone() = 0;
  virtual Protocol	&serialize(Protocol &) const = 0;
  virtual Protocol	&unserialize(Protocol &) = 0;
};

#endif /* ITRANSFORMERS_H_ */
