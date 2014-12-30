#ifndef IDATABASE_H_
# define IDATABASE_H_

# include	"ISavable.hh"

class IDatabase : public save::ISavable
{
public:
  virtual ~IDatabase() {};

public:
  virtual save::Backup &	save(save::Backup &) = 0;
  virtual save::Backup &	load(save::Backup &) = 0;
};

#endif /* IDATABASE_H_ */
