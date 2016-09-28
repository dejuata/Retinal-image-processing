#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsfilter.h"
#include "ui_settingsfilter.h"

#include "process.h"
#include "filter.h"
#include "filterminmedmax.h"
#include "resources.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   // this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Función para cargar la imagen
void MainWindow::on_actionOpen_triggered()
{
   QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Image Files (*.png *.jpg *.bmp)"));

   image.load(file);
   // convertir la imagen a formato rgb 8 bits;
   image = image.convertToFormat(QImage::Format_RGB888);

   if (!file.isEmpty())
   {
       if (!image.load(file))
       {
           QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
           return;
       }
    }

    ui->after->setPixmap(QPixmap::fromImage(image));
    ui->origin->setPixmap(QPixmap::fromImage(image));    

}
// Función para guardar la imagen transformada
void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "", tr("Images (*.png)"));

    if (!fileName.isEmpty())
    {
        if (!image.save(fileName))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        imageT.save(fileName);
     }
}

/*
 * Metodos que llaman a las funciones de convercion de formatos RGB -> RGB, YUV, YIQ, CMY, HSV, HSL, XYZ, O1O2O3
 */
void MainWindow::on_actionRGB_to_RGB_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        /* Renderizo imagenes en label miniatura, ademas las almaceno en variables globales
         * para poderlas renderizar en el label origin ademas de que se puedan enviar como parametros
         * a distintas funciones
         */
        imageT = convertToRGB(image, 'a');
        imageR = convertToRGB(image, 'r');
        imageG = convertToRGB(image, 'g');
        imageB = convertToRGB(image, 'b');

        render_Miniature_Image();

        show_Text_UI("R","G","B");
    }
}
void MainWindow::on_actionRGB_to_YUV_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        // Renderizo imagenes en label
        imageT = convertToYUV(image, 'a');
        imageR = convertToYUV(image, 'y');
        imageG = convertToYUV(image, 'u');
        imageB = convertToYUV(image, 'v');

        render_Miniature_Image();

        show_Text_UI("Y","U","V");
    }
}
void MainWindow::on_actionRGB_to_YIQ_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        // Renderizo imagenes en label
        imageT = convertToYIQ(image, 'a');
        imageR = convertToYIQ(image, 'y');
        imageG = convertToYIQ(image, 'i');
        imageB = convertToYIQ(image, 'q');

        render_Miniature_Image();

        show_Text_UI("Y","I","Q");

    }
}
void MainWindow::on_actionRGB_to_CMY_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        // Renderizo imagenes en label
        imageT = convertToCMY(image, 'a');
        imageR = convertToCMY(image, 'c');
        imageG = convertToCMY(image, 'm');
        imageB = convertToCMY(image, 'y');

        render_Miniature_Image();

        show_Text_UI("C","M","Y");
    }
}
void MainWindow::on_actionRGB_to_HSV_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        // Renderizo imagenes en label
        imageT = convertToHSV(image, 'a');
        imageR = convertToHSV(image, 'h');
        imageG = convertToHSV(image, 's');
        imageB = convertToHSV(image, 'v');

        render_Miniature_Image();

        show_Text_UI("H","S","V");
    }
}
void MainWindow::on_actionRGB_to_HSL_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        // Renderizo imagenes en label
        imageT = convertToHSL(image, 'a');
        imageR = convertToHSL(image, 'h');
        imageG = convertToHSL(image, 's');
        imageB = convertToHSL(image, 'l');

        render_Miniature_Image();

        show_Text_UI("H","S","L");
    }
}
void MainWindow::on_actionRGB_to_XYZ_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        // Renderizo imagenes en label
        imageT = convertToXYZ(image, 'a');
        imageR = convertToXYZ(image, 'x');
        imageG = convertToXYZ(image, 'y');
        imageB = convertToXYZ(image, 'z');

        render_Miniature_Image();

        show_Text_UI("X","Y","Z");

    }
}
void MainWindow::on_actionRGB_to_O1O2O3_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        // Renderizo imagenes en label
        imageT = convertToOOO(image, 'a');
        imageR = convertToOOO(image, 'x');
        imageG = convertToOOO(image, 'y');
        imageB = convertToOOO(image, 'z');

        render_Miniature_Image();

        show_Text_UI("O1","O2","O3");
    }
}

/*
 * Muestro la imagen en el label origin cada vez que se da clic al btn de la miniatura
 */
void MainWindow::on_btn_origin_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::on_btn_transform_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageT));
}
void MainWindow::on_btn_one_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageR));
}
void MainWindow::on_btn_two_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageG));
}
void MainWindow::on_btn_three_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageB));
}

/*
 *  Crea y muestra la ventana de configuracion de filtros
 */
void MainWindow::on_actionSettings_triggered()
{
    SettingsFilter *averange = new SettingsFilter(this);
    averange->setModal(true);
    averange->show();
}

/*
 * CONFIGURACIÓN DE FILTROS POR DEFAULT -> VENTANA SETTINGSFILTER
 *
 * Si la variable int selectFilter esta inicialida con estos valores, corresponde a:
 * 0 -> Filtro promedio
 * 1 -> Filtro Gaussiano
 * 2 -> Filtro Minimo
 * 3 -> Filtro Mediano
 * 4 -> Filtro Maximo
 */
void SettingsFilter::on_filterByDefault_currentIndexChanged(int index)
{
    // Filtro Promedio
    if(index == 1)
    {
        clear_options();
        // por default trabaja con el kernel promedio
        selectFilter = 0;
        // Desplegar las casillas vacias correspondientes al tamaño del filtro en pantalla
        on_selectFilter_currentIndexChanged(1);
        // Insertar los valores que trae el filtro por defecto
        show_value_kernel(listAverage, 1);
    }
    // Filtro Gaussiano
    if(index == 2)
    {
        clear_options();
        selectFilter = 1;
        qDebug()<<"Seleccione kernel gaussiano";
        on_selectFilter_currentIndexChanged(1);
        show_value_kernel(listGaussiano, 1);
    }
    // Filtro Minimo
    if(index == 3)
    {
        clear_options();
        selectFilter = 2;
        qDebug()<<"Seleccione minimo";
    }
    // Filtro Mediano
    if(index == 4)
    {
        clear_options();
        selectFilter = 3;
        qDebug()<<"Seleccione mediano";
    }
    // Filtro Maximo
    if(index == 5)
    {
        clear_options();
        selectFilter = 4;
        qDebug()<<"Seleccione maximo";
    }
    // Filtro Sigma
    if(index == 6)
    {
        selectFilter = 5;
        qDebug()<<"Seleccione sigma";
        ui->optionsLabel->show();
        ui->optionsNumber->show();
    }
    // Filtro Nagao
    if(index == 7)
    {
        selectFilter = 6;
        qDebug()<<"Seleccione nagao";
    }
}

// cargar filtros externos en archivos txt
void SettingsFilter::on_pushButton_clicked()
{
    QString text;
    QStringList lists;

    // cargo el txt con el filtro
    QFile file = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Image Files (*.txt)"));
    file.open(QIODevice::ReadOnly);

    QTextStream result(&file);

    text = result.readAll();

    // Limpiar el string
    lists = cleanMatriz(text);

    if (lists.length() == 9)
    {
        on_selectFilter_currentIndexChanged(1);
        show_value_kernel(lists, 1);
    }
    if (lists.length() == 25)
    {
        on_selectFilter_currentIndexChanged(2);
        show_value_kernel(lists, 2);
    }
    if (lists.length() == 49)
    {
        on_selectFilter_currentIndexChanged(3);
        show_value_kernel(lists, 3);
    }
    if (lists.length() == 81)
    {
        on_selectFilter_currentIndexChanged(3);
        show_value_kernel(lists, 3);
    }

    qDebug()<<"list: "<<lists;

    // Asignar a la matriz los valores del string
    createMatriz(lists);

    // Asigno este valor para indicar que el programa trabaje con la matriz cargada
    selectFilter = 9;

    ui->loaded->show();

    qDebug()<<"CARGO FILTRO";

    file.close();

}

// Si el usuario selecciona en el menu filter -> channel T
void MainWindow::on_actionTransform_triggered()
{
    action_Filter_Select(imageT);
}

void MainWindow::on_actionChannel_One_triggered()
{
    action_Filter_Select(imageR);
}

void MainWindow::on_actionChannel_Two_triggered()
{
   action_Filter_Select(imageG);
}

void MainWindow::on_actionChannel_Three_triggered()
{
    action_Filter_Select(imageB);
}
