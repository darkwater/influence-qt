#include "bookmarkdelegate.h"
#include <QStyledItemDelegate>
#include <QApplication>
#include <QDebug>
#include <QPainter>



BookmarkDelegate::BookmarkDelegate() :
    margins(10, 5, 10, 5)
{
}

void BookmarkDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_ASSERT(index.isValid());

    if (index.data().toString().length() == 0) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(29, 31, 33));
        painter->drawRect(option.rect - QMargins(10, 4, 10, 4));
        return;
    }

    QStyledItemDelegate::paint(painter, option, index);
}

QSize BookmarkDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().toString().length() == 0)
        return QSize(0, 10);

    return QStyledItemDelegate::sizeHint(option, index);
}
