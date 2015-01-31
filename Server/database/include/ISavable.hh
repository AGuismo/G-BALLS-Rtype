// -----------------------------------------------------------------------------
// ISAVABLE
// -----------------------------------------------------------------------------

#pragma once

namespace save
{
    class Backup;

    class ISavable
    {
	public:
	virtual ~ISavable() {}

	public:
	virtual save::Backup &	save(save::Backup &) = 0;
	virtual save::Backup &	load(save::Backup &) = 0;
    };
}
