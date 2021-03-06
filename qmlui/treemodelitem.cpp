/*
  Q Light Controller Plus
  treemodelitem.cpp

  Copyright (c) Massimo Callegari

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <QQmlEngine>
#include <QDebug>

#include "treemodelitem.h"
#include "treemodel.h"

TreeModelItem::TreeModelItem(QString label, QObject *parent)
    : QObject(parent)
    , m_label(label)
{
    m_path = QString();
    m_isExpanded = false;
    m_isSelected = false;
    m_children = NULL;
}

TreeModelItem::~TreeModelItem()
{
    //qDebug() << "!!! WARNING TreeModelItem destroyed WARNING !!!";
    if (hasChildren())
    {
        m_children->clear();
        delete m_children;
        m_children = NULL;
    }
}

QString TreeModelItem::label() const
{
    return m_label;
}

void TreeModelItem::setLabel(QString label)
{
    m_label = label;
}

QString TreeModelItem::path() const
{
    return m_path;
}

void TreeModelItem::setPath(QString path)
{
    m_path = path;
}

bool TreeModelItem::isExpanded() const
{
    return m_isExpanded;
}

void TreeModelItem::setExpanded(bool expanded)
{
    m_isExpanded = expanded;
}

bool TreeModelItem::isSelected() const
{
    return m_isSelected;
}

void TreeModelItem::setSelected(bool selected)
{
    m_isSelected = selected;
}

QVariant TreeModelItem::data(int index)
{
    //qDebug() << "Getting data at" << index << label();
    if (index < 0 || index >= m_data.count())
        return QVariant();

    return m_data.at(index);
}

void TreeModelItem::setData(QVariantList data)
{
    m_data = data;
}

bool TreeModelItem::setChildrenColumns(QStringList columns)
{
    bool childrenTreeCreated = false;
    if (m_children == NULL)
    {
        m_children = new TreeModel();
        QQmlEngine::setObjectOwnership(m_children, QQmlEngine::CppOwnership);
        childrenTreeCreated = true;
    }
    m_children->setColumnNames(columns);

    return childrenTreeCreated;
}

bool TreeModelItem::addChild(QString label, QVariantList data, bool sorting, QString path)
{
    bool childrenTreeCreated = false;
    if (m_children == NULL)
    {
        m_children = new TreeModel();
        QQmlEngine::setObjectOwnership(m_children, QQmlEngine::CppOwnership);
        childrenTreeCreated = true;
    }
    m_children->enableSorting(sorting);
    m_children->addItem(label, data, path);

    return childrenTreeCreated;
}

bool TreeModelItem::hasChildren()
{
    if (m_children != NULL)
        return true;

    return false;
}

TreeModel *TreeModelItem::children()
{
    return m_children;
}

void TreeModelItem::printItem(int tab)
{
    qDebug() << QString("%1%2").arg(QString(tab, QChar(0x20))).arg(label()) << m_data;
}


