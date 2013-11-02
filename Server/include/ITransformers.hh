#ifndef ITRANSFORMERS_H_
# define ITRANFORMERS_H_

class ITransformers
{
public:
  virtual ~ITransformers() {};

public:
  virtual Protocol	&Megan(Protocol &) = 0;
  virtual Protocol	&Fox(Protocol &) = 0;
};

#endif /* ITRANSFORMERS_H_ */
