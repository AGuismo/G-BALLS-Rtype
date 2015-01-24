#ifndef ISERIALIZABLE_H_
# define ITRANFORMERS_H_

class	Protocol;
class	ARequest;

class ISerializable
{
public:
  virtual ~ISerializable() {};

public:
  virtual ARequest	*clone() const = 0;
  virtual Protocol	&serialize(Protocol &) const = 0;
  virtual Protocol	&unserialize(Protocol &) = 0;
};

#endif /* ISERIALIZABLE_H_ */
