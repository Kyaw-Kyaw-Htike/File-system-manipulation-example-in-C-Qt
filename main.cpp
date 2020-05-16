#include <QtCore/QCoreApplication>
#include <QDirIterator>
#include <QDir>
#include <QDebug>


/*
Imagine the following directory structure:
- C
-- Selfies
--- Ali
---- img1.png
---- img2.jpg
---- img3.png
--- Sam
---- img1.png
---- img2.jpg
--- Peter
---- img1.tif
---- img2.tiff
---- img3.png
---- img4.png

The following code goes through each of the subdirectories inside the "Selfies" folder. Inside each subfolder, it finds each image and print out the full path. The console output will be something like:

The directory is "C/Selfies/Combined"
# of subdirs found = 3
===========================
===========================
"Ali"
# of images for this person = 3
"C:/Selfies/Ali/img1.png"
"C:/Selfies/Ali/img2.jpg"
"C:/Selfies/Ali/img3.png"
===========================
===========================
"Sam"
# of images for this person = 2
"C:/Selfies/Sam/img1.png"
"C:/Selfies/Sam/img2.jpg
===========================
===========================
"Peter"
# of images for this person = 4
"C:/Selfies/Peter/img1.tif"
"C:/Selfies/Peter/img2.tiff"
"C:/Selfies/Peter/img3.png"
"C:/Selfies/Peter/img4.png"
===========================
Total # images for all people = 9

*/

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QString dir_enroll = "C:/Selfies";
	QStringList extensions_img_search;  
	extensions_img_search << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp" << "*.tif" << "*.tiff";
	qDebug() << "The directory is" << dir_enroll;
	QDir dd(dir_enroll);
	QFileInfoList subdirs = dd.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	qDebug() << "# of subdirs found =" << subdirs.size();
	size_t total_num_imgs = 0;
	qDebug() << "===========================";
	for (size_t i = 0; i < subdirs.size(); i++)
	{
		qDebug() << "===========================";
		QString name_subdir = subdirs[i].fileName();
		qDebug() << name_subdir;
		QDir dir_enroll_person = QDir(dd.filePath(subdirs[i].fileName()));
		QFileInfoList fpaths_imgs_person = dir_enroll_person.entryInfoList(extensions_img_search, QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
		qDebug() << "# of images for this person =" << fpaths_imgs_person.size();
		total_num_imgs += fpaths_imgs_person.size();
		for (size_t j = 0; j < fpaths_imgs_person.size(); j++)
		{
			QString fpath_img_person = fpaths_imgs_person[j].absoluteFilePath();
			qDebug() << fpath_img_person;
		}
		qDebug() << "===========================";
	}
	qDebug() << "Total # images for all people =" << total_num_imgs;
		
	return a.exec();
}

