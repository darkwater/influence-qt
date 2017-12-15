#ifndef BOOKMARKDELEGATE_H
#define BOOKMARKDELEGATE_H

#include <QStyledItemDelegate>



class BookmarkDelegate : public QStyledItemDelegate
{
public:
    BookmarkDelegate();

private:
    QMargins margins;

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // BOOKMARKDELEGATE_H
