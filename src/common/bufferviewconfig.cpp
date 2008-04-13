/***************************************************************************
 *   Copyright (C) 2005-08 by the Quassel Project                          *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "bufferviewconfig.h"

#include "bufferinfo.h"

BufferViewConfig::BufferViewConfig(int bufferViewId, QObject *parent)
  : SyncableObject(parent),
    _bufferViewId(bufferViewId),
    _addNewBuffersAutomatically(true),
    _sortAlphabetically(true),
    _hideInactiveBuffers(false),
    _allowedBufferTypes(BufferInfo::StatusBuffer | BufferInfo::ChannelBuffer | BufferInfo::QueryBuffer | BufferInfo::GroupBuffer),
    _minimumActivity(0)
{
  setObjectName(QString::number(bufferViewId));
}

BufferViewConfig::BufferViewConfig(int bufferViewId, const QVariantMap &properties, QObject *parent)
  : SyncableObject(parent),
    _bufferViewId(bufferViewId)
{
  fromVariantMap(properties);
  setObjectName(QString::number(bufferViewId));
}

void BufferViewConfig::setBufferViewName(const QString &bufferViewName) {
  if(_bufferViewName == bufferViewName)
    return;

  _bufferViewName = bufferViewName;
  emit bufferViewNameSet(bufferViewName);
}

void BufferViewConfig::setNetworkId(const NetworkId &networkId) {
  if(_networkId == networkId)
    return;

  _networkId = networkId;
  emit networkIdSet(networkId);
}

void BufferViewConfig::setAddNewBuffersAutomatically(bool addNewBuffersAutomatically) {
  if(_addNewBuffersAutomatically == addNewBuffersAutomatically)
    return;

  _addNewBuffersAutomatically = addNewBuffersAutomatically;
  emit addNewBuffersAutomaticallySet(addNewBuffersAutomatically);
}

void BufferViewConfig::setSortAlphabetically(bool sortAlphabetically) {
  if(_sortAlphabetically == sortAlphabetically)
    return;

  _sortAlphabetically = sortAlphabetically;
  emit sortAlphabeticallySet(sortAlphabetically);
}

void BufferViewConfig::setAllowedBufferTypes(int bufferTypes) {
  if(_allowedBufferTypes == bufferTypes)
    return;

  _allowedBufferTypes = bufferTypes;
  emit allowedBufferTypesSet(bufferTypes);
}

void BufferViewConfig::setMinimumActivity(int activity) {
  if(_minimumActivity == activity)
    return;

  _minimumActivity = activity;
  emit minimumActivitySet(activity);
}

void BufferViewConfig::setHideInactiveBuffers(bool hideInactiveBuffers) {
  if(_hideInactiveBuffers == hideInactiveBuffers)
    return;

  _hideInactiveBuffers = hideInactiveBuffers;
  emit hideInactiveBuffersSet(hideInactiveBuffers);
}

QVariantList BufferViewConfig::initBufferList() const {
  QVariantList buffers;

  foreach(BufferId bufferId, _buffers) {
    buffers << qVariantFromValue(bufferId);
  }

  return buffers;
}

void BufferViewConfig::initSetBufferList(const QVariantList &buffers) {
  _buffers.clear();

  foreach(QVariant buffer, buffers) {
    _buffers << buffer.value<BufferId>();
  }

  emit bufferListSet();
}

void BufferViewConfig::initSetBufferList(const QList<BufferId> &buffers) {
  _buffers.clear();

  foreach(BufferId bufferId, buffers) {
    _buffers << bufferId;
  }

  emit bufferListSet();
}

void BufferViewConfig::addBuffer(const BufferId &bufferId, int pos) {
  if(_buffers.contains(bufferId))
    return;
  
  _buffers.insert(pos, bufferId);
  emit bufferAdded(bufferId, pos);
}

void BufferViewConfig::moveBuffer(const BufferId &bufferId, int pos) {
  if(!_buffers.contains(bufferId))
    return;

  _buffers.move(_buffers.indexOf(bufferId), pos);
  emit bufferMoved(bufferId, pos);
}

void BufferViewConfig::removeBuffer(const BufferId &bufferId) {
  if(!_buffers.contains(bufferId))
    return;
  
  _buffers.removeAt(_buffers.indexOf(bufferId));
  emit bufferRemoved(bufferId);
}
