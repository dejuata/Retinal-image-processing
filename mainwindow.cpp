#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsfilter.h"
#include "ui_settingsfilter.h"
#include "convertImage.h"
#include "filter.h"
#include "histograma.h"
#include "resources.h"
#include "threshold.h"

using namespace std;

// variable para almacenar el tamaño de la imagen, este valor cambia cuando cargo la imagen
int sizeImage = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    ui->histograma->hide();


    this->setWindowState(Qt::WindowMaximized);
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
   imageLabel = &image;

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

    // Funcion que limpia los label cada vez que se abre una nueva imagen
    clear_Label_Miniature_Image();

    qDebug()<<image.isGrayscale();

    // almaceno el tamaño de la imagen en una variable global para poder usarla en el algoritmo de otsu
    sizeImage = image.width() * image.height();
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

/*-----------------------------------------------------------------------------------------------------------/*
 * Metodos que llaman a las funciones de convercion de formatos RGB -> RGB, YUV, YIQ, CMY, HSV, HSL, XYZ, O1O2O3
 *-----------------------------------------------------------------------------------------------------------*/
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
        channelR = "Red", channelG = "Green", channelB = "Blue";

        futureRGB();

        render_Miniature_Image();
        show_Text_UI("R","G","B");
        show_Label_Image_Hide_Histograma(0);
    }
}
void MainWindow::on_actionRGB_to_YYY_triggered()
{
    if (image.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    else
    {
        channelR = "Red", channelG = "Green", channelB = "Blue";

        futureYYY();

        render_Miniature_Image(false);
        show_Text_UI("Y","Y","Y");
        show_Label_Image_Hide_Histograma(0);
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
        channelR = "Y", channelG = "U", channelB = "V";

        // Renderizo imagenes en label
        futureYUV();

        render_Miniature_Image();
        show_Text_UI("Y","U","V");
        show_Label_Image_Hide_Histograma(0);
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
        channelR = "Y", channelG = "I", channelB = "Q";

        // Renderizo imagenes en label
        futureYIQ();

        render_Miniature_Image();
        show_Text_UI("Y","I","Q");
        show_Label_Image_Hide_Histograma(0);
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
        channelR = "Cyan", channelG = "Magenta", channelB = "Yellow";

        // Renderizo imagenes en label
        futureCMY();

        render_Miniature_Image();
        show_Text_UI("C","M","Y");
        show_Label_Image_Hide_Histograma(0);
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
        channelR = "Hue", channelG = "Saturation", channelB = "Value";

        // Renderizo imagenes en label
        futureHSV();

        render_Miniature_Image();
        show_Text_UI("H","S","V");
        show_Label_Image_Hide_Histograma(0);
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
        channelR = "Hue", channelG = "Saturation", channelB = "Ligntness";

        // Renderizo imagenes en label
        futureHSL();

        render_Miniature_Image();
        show_Text_UI("H","S","L");
        show_Label_Image_Hide_Histograma(0);
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
        channelR = "X", channelG = "Y", channelB = "Z";

        // Renderizo imagenes en label
        futureXYZ();

        render_Miniature_Image();
        show_Text_UI("X","Y","Z");
        show_Label_Image_Hide_Histograma(0);
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
        channelR = "O1", channelG = "O2", channelB = "O3";

        // Ejecuto las funciones de procesamiento para cada canal en un hilo respectivo
        futureOOO();

        render_Miniature_Image();
        show_Text_UI("O1","O2","O3");
        show_Label_Image_Hide_Histograma(0);
    }
}
/*-----------------------------------------------------------------------------------------------------------/*
 * Fin
 *-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------/*
 * Muestro la imagen en el label origin (label principal) cada vez que se da clic al btn de la miniatura
 *-----------------------------------------------------------------------------------------------------------*/
void MainWindow::on_btn_origin_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(image));
    // Almaceno en un puntero la imagen que selecciona el usuario para poder aplicar las diferentes operaciones
    imageLabel = &image;
    show_Label_Image_Hide_Histograma(0);
}
void MainWindow::on_btn_transform_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageT));
    imageLabel = &imageT;
    show_Label_Image_Hide_Histograma(0);
}
void MainWindow::on_btn_one_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageR));
    imageLabel = &imageR;
    show_Label_Image_Hide_Histograma(1);
}
void MainWindow::on_btn_two_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageG));
    imageLabel = &imageG;
    show_Label_Image_Hide_Histograma(2);
}
void MainWindow::on_btn_three_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(imageB));
    imageLabel = &imageB;
    show_Label_Image_Hide_Histograma(3);
}
/*-----------------------------------------------------------------------------------------------------------/*
 * Fin
 *-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------/*
 * Ventana del menu Filter
 *-----------------------------------------------------------------------------------------------------------*/
//  Crea y muestra la ventana de configuracion de filtros
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
 * 5 -> Filtro Sigma
 * 6 -> Filtro Nagao
 */

// funcion que setea el valor de una variable global llamada selectFilter
// para poder saber que funcion debo llamar para poder aplicarle el filtro a la imagen
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

// Funcion que lee un filtro de un archivo txt, el filtro puede contener un kernel de 3x3, 5x5, 7x7 y 9x9
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

// Si el usuario selecciona en el menu filter -> channel T o channel R, etc,
// llama a una funcion que aplicar el filtro seleccionado en la ventana settings y lo aplica
// a la imagen que corresponde
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
/*-----------------------------------------------------------------------------------------------------------/*
 * Fin
 *-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------/*
 * Filtros configurados como botones
 *-----------------------------------------------------------------------------------------------------------*/
/* Paso bajo */
void MainWindow::on_btnAverage_clicked()
{
    createMatriz(listAverage);
    ui->origin->setPixmap(QPixmap::fromImage(filterAverageAndGaussiano(*imageLabel, 3, "average")));
}
void MainWindow::on_btnGaussiano_clicked()
{
    createMatriz(listGaussiano);
    ui->origin->setPixmap(QPixmap::fromImage(filterAverageAndGaussiano(*imageLabel, 3, "gaussiano")));
}
void MainWindow::on_btnMinimum_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(filterMinMedMax(*imageLabel, 0)));
}
void MainWindow::on_btnMedium_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(filterMinMedMax(*imageLabel, 1)));
}
void MainWindow::on_btnMaximum_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(filterMinMedMax(*imageLabel, 2)));
}
void MainWindow::on_btnSigma_clicked()
{
     ui->origin->setPixmap(QPixmap::fromImage(filterSigma(*imageLabel,numberSigma)));
}
void MainWindow::on_sliderSigma_sliderReleased()
{
    numberSigma = sigma();
    qDebug()<<numberSigma;
    ui->origin->setPixmap(QPixmap::fromImage(filterSigma(*imageLabel,numberSigma)));
}
void MainWindow::on_btnNagao_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(filterNagao(*imageLabel)));
}
/* Paso alto */

// Metodo que retorna el valor del threshold del spin box seleccionado por el usuario
int MainWindow::threshold()
{
    return ui->threshold->value();
}

// Metodo que retorna true o false si el fondo es blanco o negro
bool MainWindow::background()
{
    return ui->white->isChecked() ? true : false;
}

void MainWindow::on_btnSobel_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(filterSobel(*imageLabel, threshold(), background())));
}
void MainWindow::on_btnRobert_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(filterRobert(*imageLabel, threshold(), background())));
}
void MainWindow::on_btnPrewitt_clicked()
{
    ui->origin->setPixmap(QPixmap::fromImage(filterPrewitt(*imageLabel, threshold(), background())));
}
/*-----------------------------------------------------------------------------------------------------------/*
 * Fin
 *-----------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------/*
 * Histograma
 *-----------------------------------------------------------------------------------------------------------*/
// Metodo que almacena en una variable global el indice del combo box el cual me indica
// que canal RGB quiero que cree el histograma y lo renderize en una miniatura
void MainWindow::on_selectChannelHistograma_currentIndexChanged(int index)
{
    selectChannelHistograma = index;
    render_Histograma_Min_Or_Max(false);
}

// Metodo que renderiza el histograma en su tamaño maximo al ser clickeado el btn
void MainWindow::on_btn_histograma_clicked()
{
    ui->origin->hide();
    ui->histograma->show();

    render_Histograma_Min_Or_Max(true);
}

// Metodo que ecualiza el histograma de la imagen dependiendo del valor almacenado
// en la variable global selectChannelHistograma
void MainWindow::on_equalizarHistograma_clicked()
{
    // asignar a las imagenes el resultado correspondendiente de equalizar el histograma para cada canal
    if(selectChannelHistograma == 0)
    {
        imageT = equalization_Histograma(imageT,selectChannelHistograma);
        imageLabel = &imageT;
    }
    if(selectChannelHistograma == 1)
    {
        imageR = equalization_Histograma(imageR,selectChannelHistograma);
        imageLabel = &imageR;
    }
    if(selectChannelHistograma == 2)
    {
        imageG = equalization_Histograma(imageG,selectChannelHistograma);
        imageLabel = &imageG;
    }
    if(selectChannelHistograma == 3)
    {
        imageB = equalization_Histograma(imageB,selectChannelHistograma);
        imageLabel = &imageB;
    }

    // renderizar imagenes en miniatura
    render_Miniature_Image();

    // Renderizar la imagen si el histograma cambia, este efecto sucede si el label esta activo -> show()
    ui->origin->setPixmap(QPixmap::fromImage(*imageLabel));

    // Crear y mostrar el histograma en el QGraphicsScene Maximum
    create_Histograma(*imageLabel,selectChannelHistograma,true);

    // Crear y mostrar el histograma en el QGraphicsScene Minimum
    create_Histograma(*imageLabel,selectChannelHistograma,false);
}

/* Operaciones con histogramas */

// Funcion que captura el valor del spin box cuando cambia
void MainWindow::on_const_2_valueChanged(double arg1)
{
    numberOperationsHistograma = arg1;
}

// Funcion que aplica a la imagen el valor gama del slider seleccionado automaticamente
void MainWindow::on_gamma_sliderReleased()
{
    QImage gamma;
    if(selectChannelHistograma == 0)
    {
        gamma = gammaConstImage(imageT,numberOperationsHistograma,0);
        imageLabel = &gamma;
    }
    if(selectChannelHistograma == 1)
    {
        gamma = gammaConstImage(imageR,numberOperationsHistograma,1);
        imageLabel = &gamma;
    }
    if(selectChannelHistograma == 2)
    {
        gamma = gammaConstImage(imageG,numberOperationsHistograma,2);
        imageLabel = &gamma;
    }
    if(selectChannelHistograma == 3)
    {
        gamma = gammaConstImage(imageB,numberOperationsHistograma,3);
        imageLabel = &gamma;
    }


    render_Miniature_Image();
    ui->origin->setPixmap(QPixmap::fromImage(*imageLabel));
    // Crear y mostrar el histograma en el QGraphicsScene Maximum
    create_Histograma(*imageLabel,selectChannelHistograma,true);
    // Crear y mostrar el histograma en el QGraphicsScene Minimum
    create_Histograma(*imageLabel,selectChannelHistograma,false);
}

// Funcion que suma una constante al histograma
void MainWindow::on_btnPlus_clicked()
{
    if(selectChannelHistograma == 0)
    {
        imageT = sumConstImage(imageT,numberOperationsHistograma,0);
        imageLabel = &imageT;
    }
    if(selectChannelHistograma == 1)
    {
        imageR = sumConstImage(imageR,numberOperationsHistograma,1);
        imageLabel = &imageR;
    }
    if(selectChannelHistograma == 2)
    {
        imageG = sumConstImage(imageG,numberOperationsHistograma,2);
        imageLabel = &imageG;
    }
    if(selectChannelHistograma == 3)
    {
        imageB = sumConstImage(imageB,numberOperationsHistograma,3);
        imageLabel = &imageB;
    }

    render_Miniature_Image();
    ui->origin->setPixmap(QPixmap::fromImage(*imageLabel));
    // Crear y mostrar el histograma en el QGraphicsScene Maximum
    create_Histograma(*imageLabel,selectChannelHistograma,true);
    // Crear y mostrar el histograma en el QGraphicsScene Minimum
    create_Histograma(*imageLabel,selectChannelHistograma,false);
}

// Funcion que setea en el spinbox el valor del slider que corresponde al numero gamma
void MainWindow::on_gamma_sliderMoved(int position)
{
    ui->const_2->setValue(position*0.001);
}

// Funcion que resta una constante al histograma
void MainWindow::on_btnSubstract_clicked()
{
    if(selectChannelHistograma == 0)
    {
        imageT = susbtractConstImage(imageT,numberOperationsHistograma,0);
        imageLabel = &imageT;
    }
    if(selectChannelHistograma == 1)
    {
        imageR = susbtractConstImage(imageR,numberOperationsHistograma,1);
        imageLabel = &imageR;
    }
    if(selectChannelHistograma == 2)
    {
        imageG = susbtractConstImage(imageG,numberOperationsHistograma,2);
        imageLabel = &imageG;
    }
    if(selectChannelHistograma == 3)
    {
        imageB = susbtractConstImage(imageB,numberOperationsHistograma,3);
        imageLabel = &imageB;
    }


    render_Miniature_Image();
    ui->origin->setPixmap(QPixmap::fromImage(*imageLabel));
    // Crear y mostrar el histograma en el QGraphicsScene Maximum
    create_Histograma(*imageLabel,selectChannelHistograma,true);
    // Crear y mostrar el histograma en el QGraphicsScene Minimum
    create_Histograma(*imageLabel,selectChannelHistograma,false);
}

/*-----------------------------------------------------------------------------------------------------------/*
 * Fin
 *-----------------------------------------------------------------------------------------------------------*/



int MainWindow::sigma()
{
    return ui->numberSigma->value();
}




void MainWindow::on_horizontalSlider_sliderReleased()
{
   // on_btnSobel_clicked();
}






// calcula el threshold con el algoritmo de otsu o isodata
// dependienda de la opcion del radio button que halla escogido el usuario
void MainWindow::on_btnThreshold_clicked()
{
    int threshold = thresholdOtsu();
    ui->threshold->setValue(threshold);
    ui->horizontalSlider->setValue(threshold);
}
