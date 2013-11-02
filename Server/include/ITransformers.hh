#ifndef ITRANSFORMERS_H_
# define ITRANFORMERS_H_

class Protocol;

class ITransformers
{
public:
  virtual ~ITransformers() {};

public:
  virtual Protocol	&Megan_serialize(Protocol &) = 0;
  virtual Protocol	&Fox_unserialize(Protocol &) = 0;
};

#endif /* ITRANSFORMERS_H_ */
