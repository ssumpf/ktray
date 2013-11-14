/**
 * \brief  A simple Qt based system tray keyboard-layout-status indicator
 * \author Sebastian Sumpf <sebastian.sumpf@genode-labs.com>
 * \date   2013-11-14
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 <Sebastian Sumpf>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <QApplication>
#include <QSystemTrayIcon>
#include <QPainter>
#include <QDialog>
#include <QDebug>

class Win : public QDialog
{
	private:

		QSystemTrayIcon *_tray;

		void _update_icon()
		{
			QStringList lang = QString(qApp->keyboardInputLocale().name()).split("_");
			QPixmap pix(15, 15);
			pix.fill(QColor(0, 0, 0, 0));

			QPainter paint(&pix);
			paint.setFont(QFont("Arial", 8));
			paint.drawText(0, 10, lang[1]);

			QIcon icon(pix);

			_tray->setIcon(icon);
			_tray->setToolTip(lang[1]);
			_tray->show();
		}

	protected:

		bool event(QEvent *event)
		{
			if (event->type() != QEvent::KeyboardLayoutChange) {
				event->ignore();
				return false;
			}
			event->accept();
			_update_icon();
			return true;
		}

	public:

		Win()
		{
			_tray = new QSystemTrayIcon();
			_update_icon();
			hide();
		}
};

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	Win win;
	return app.exec();
}
