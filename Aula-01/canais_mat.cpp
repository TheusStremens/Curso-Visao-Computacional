#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Vamos brincar com uma bela imagem.
    cv::Mat imagem = cv::imread("Aula-01/images/natureza.jpg");
    cv::imshow("Natureza", imagem);
    cv::waitKey(0);

    // Vamos percorrer a imagem e zerar o canal Blue.
    cv::Mat imagem_editada = imagem.clone();
    for (int row = 0; row < imagem_editada.rows; row++)
    {
        for (int col = 0; col < imagem_editada.cols; col++)
        {
            // Estamos pegando o ponteiro para cada pixel na imagem.
            cv::Vec3b &pixel = imagem_editada.at<cv::Vec3b>(row, col);
            // As imagens coloridas estão em BGR, então temos que zerar o
            // primeiro canal.
            pixel[0] = 0;
        }
    }
    cv::imshow("Natureza sem Blue", imagem_editada);
    cv::waitKey(0);

    // Ficou horrivel ne? Essa imagem é muito iluminada, que tal nós reduzirmos
    // um pouco essa exuberância? Podemos retirar um pouco de cor de cada canal.
    imagem_editada = imagem.clone();
    for (int row = 0; row < imagem_editada.rows; row++)
    {
        for (int col = 0; col < imagem_editada.cols; col++)
        {
            // Estamos pegando o ponteiro para cada pixel na imagem.
            cv::Vec3b &pixel = imagem_editada.at<cv::Vec3b>(row, col);
            // Vamos reduzir 60 em cada canal.
            pixel = pixel - cv::Vec3b(60, 60, 60);
        }
    }
    cv::imshow("Natureza mais dark", imagem_editada);
    cv::waitKey(0);

    // E se quisermos ver apenas o canal Red? Tipo aquele efeito Sim City.
    imagem_editada = imagem.clone();
    for (int row = 0; row < imagem_editada.rows; row++)
    {
        for (int col = 0; col < imagem_editada.cols; col++)
        {
            cv::Vec3b &pixel = imagem_editada.at<cv::Vec3b>(row, col);
            // Vamos zerar o Blue e o Green.
            pixel[0] = 0;
            pixel[1] = 0;
        }
    }
    cv::imshow("Natureza Sim City?", imagem_editada);
    cv::waitKey(0);
    cv::destroyAllWindows();
    // Não ficou parecido com o efeito Sim City, a imagem ficou escura. Fizemos
    // da forma errada, o correto seria transformar a imagem para preto e branco
    // e depois habilitar so a cor vermelha. Existem diversas formas de fazer
    // isso, eu vou mostrar algumas delas.
    imagem_editada = imagem.clone();
    for (int row = 0; row < imagem_editada.rows; row++)
    {
        for (int col = 0; col < imagem_editada.cols; col++)
        {
            cv::Vec3b &pixel = imagem_editada.at<cv::Vec3b>(row, col);
            // O valor grayscale desse pixel pode ser a média dos valores.
            auto media = (pixel[0] + pixel[1] + pixel[2]) / 3;
            // Se a cor vermelha é a mais presente, mantemos a cor do pixel, do
            // contrario deixamos em grayscale.
            if (pixel[2] > pixel[0] && pixel[2] > pixel[1])
                continue;
            pixel[0] = media;
            pixel[1] = media;
            pixel[2] = media;
        }
    }
    cv::imshow("Natureza Sim City 1", imagem_editada);
    cv::waitKey(0);

    // Os tons amarelos/laranja apareceram. Temos que aumentar a margem de
    // presença do vermelho.
    imagem_editada = imagem.clone();
    for (int row = 0; row < imagem_editada.rows; row++)
    {
        for (int col = 0; col < imagem_editada.cols; col++)
        {
            cv::Vec3b &pixel = imagem_editada.at<cv::Vec3b>(row, col);
            // O valor grayscale desse pixel pode ser a média dos valores.
            auto media = (pixel[0] + pixel[1] + pixel[2]) / 3;
            // Se a cor vermelha é a mais presente, mantemos a cor do pixel, do
            // contrario deixamos em grayscale.
            if (pixel[2] > 2 * pixel[0] && pixel[2] > 2 * pixel[1])
                continue;
            pixel[0] = media;
            pixel[1] = media;
            pixel[2] = media;
        }
    }
    cv::imshow("Natureza Sim City 2", imagem_editada);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // Se queremos mexer nos canais, podemos fazer isso com os ponteiros para
    // os pixels, mas existe uma forma muito mais rápida de fazer isso. Por
    // exemplo, como zerar o canal Red.
    std::vector<cv::Mat> bgr;
    cv::split(imagem, bgr);
    // brg[0] = Mat com os valores do canal Blue.
    // brg[1] = Mat com os valores do canal Green.
    // brg[2] = Mat com os valores do canal Red.
    bgr[2] *= 0; // Zeramos o Red.
    // Agora é só montar a imagem novamente.
    cv::merge(bgr, imagem_editada);
    cv::imshow("Natureza sem Red", imagem_editada);
    cv::waitKey(0);

    // Podemos trocar a ordem dos canais e criar uma imagem muito louca.
    cv::split(imagem, bgr);
    cv::Mat aux = bgr[0].clone();
    bgr[0] = bgr[1].clone();
    bgr[1] = aux.clone();
    cv::merge(bgr, imagem_editada);
    cv::imshow("Natureza dois canais trocados", imagem_editada);
    cv::waitKey(0);

    return 0;
}