/*
 * guildshell.h
 *
 *  ShowEQ Distributed under GPL
 *  http://www.sourceforge.net/projects/seq
 *
 *  Copyright 2004 Zaphod (dohpaz@users.sourceforge.net). 
 *
 */

#ifndef _GUILDSHELL_H_
#define _GUILDSHELL_H_

#include <stdint.h>
#include <time.h>

#include <qstring.h>
#include <qobject.h>
#include <qdict.h>

//----------------------------------------------------------------------
// forward declarations
class QTextStream;

class NetStream;
class ZoneMgr;

struct GuildMemberUpdate;

//----------------------------------------------------------------------
// GuildMember
class GuildMember
{
 public:
  GuildMember(NetStream& netStream);
  ~GuildMember();

  void update(const GuildMemberUpdate* gmu);

  const QString& name() const { return m_name; }
  uint8_t level() const { return m_level; }
  uint8_t classVal() const { return m_class; }
  QString classString() const;
  uint32_t guildRank() const { return m_guildRank; }
  const QString& guildRankString() const;
  uint32_t bankRank() const { return m_banker; }
  const QString& bankRankString() const;
  uint32_t altRank() const { return m_alt; }
  const QString& altRankString() const;
  uint32_t memberRank() const { return m_fullmember; }
  const QString& memberRankString() const;
  time_t lastOn() const { return m_lastOn; }
  const QString& publicNote() const { return m_publicNote; }
  uint16_t zoneId() const { return m_zoneId; }
  uint16_t zoneInstance() const { return m_zoneInstance; }

 protected:
  QString m_name;
  uint8_t m_banker; // 0 = no, 1 = banker
  uint8_t m_level;
  uint8_t m_class;
  uint32_t m_guildRank; // 0 = member, 1 = officer, 2 = leader
  time_t m_lastOn;
  uint8_t m_guildTributeOn; // 0 = off, 1 = on
  uint8_t m_guildTrophyOn; // 0 = off, 1 = on
  uint8_t m_guildTributeDonated;
  time_t m_guildTributeLastDonation;
  uint32_t m_alt; // 0 = no, 1 = alt
  uint32_t m_fullmember; // 0 = prospect, 1 = fullmember
  QString m_publicNote;
  uint16_t m_zoneId;
  uint16_t m_zoneInstance;
};

//----------------------------------------------------------------------
// GuildMemberDict
typedef QDict<GuildMember> GuildMemberDict;
typedef QDictIterator<GuildMember> GuildMemberDictIterator;

//----------------------------------------------------------------------
// GuildShell
class GuildShell : public QObject
{
  Q_OBJECT
 public:
  GuildShell(ZoneMgr* zoneMgr, QObject* parent = 0, const char* name = 0);
  ~GuildShell();
  const GuildMemberDict& members() { return m_members; }
  size_t maxNameLength() { return m_maxNameLength; }

  void dumpMembers(QTextStream& out);
  
  QString zoneString(uint16_t zoneid) const;

 public slots:
  void guildMemberList(const uint8_t* data, size_t len);
  void guildMemberUpdate(const uint8_t* data, size_t len);

 signals:
  void cleared();
  void loaded();
  void added(const GuildMember* gm);
  void removed(const GuildMember* gm);
  void updated(const GuildMember* gm);

 protected:

  GuildMemberDict m_members;
  size_t m_maxNameLength;
  ZoneMgr* m_zoneMgr;
};

#endif // _GUILDSHELL_H_
