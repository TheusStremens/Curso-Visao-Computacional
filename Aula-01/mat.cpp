#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Essa Mat é completamente vazia, como um ponteiro apontando para o nada.
    cv::Mat imagem;
    // Essa Mat é uma imagem em grayscale, toda preta. O Size é (width, height),
    // lembre sempre disso. CV_8U é o tipo de dado armazenado. Os mais comuns
    // são:
    // CV_8U - Unsigned 8bits uchar 0~255 (1 canal, usado em imagens em
    // grayscale)
    // CV_8UC3 - O mesmo que CV_8U, só que são três canais, usado em imagens
    // coloridas
    // CV_32FC3 - Float 32bits float -1.1810-38~3.4010-38  (três canais de
    // float, usado para representar point clouds)
    cv::Mat imagem_preta = cv::Mat::zeros(cv::Size(400, 100), CV_8U);

    // Vamos exibir essas imagens com o imshow
    cv::imshow("Imagem preta", imagem_preta);
    // O imshow cria uma janela e mata-a logo em seguida. Para que você possa
    // visuzaliar a imagem, temos que pausar a execução do programa. A forma
    // usual de fazer isso é fazer o programa esperar por uma tecla com o
    // waitKey. Você poderia fazer com std::cin tb, mas waitKey é o mais usado.
    // Se você passar um valor diferente de 0 como argumento, ele vai esperar
    // apenas aquela quantidade de tempo (em milisegundos).
    cv::waitKey(0);
    // ! Se vc tentar fazer um imshow de `imagem` vai dar seg fault.

    // Agora vamos tentar criar uma imagem toda branca. Seria usando ::ones?
    cv::Mat imagem_branca = cv::Mat::ones(cv::Size(400, 100), CV_8U);
    cv::imshow("Imagem branca?", imagem_branca);
    cv::waitKey(0);
    // A imagem não é branca. O motivo é que imagens em grayscale vão de 0
    // (preto) até 255 (branco). Uma Mat com 1 é praticamente uma Mat toda
    // preta. Podemos usar adição pra gerar uma imagem branca.
    imagem_branca = imagem_branca + 254;
    cv::imshow("Imagem branca", imagem_branca);
    cv::waitKey(0);

    // Para não ficar um bolo de janelas com imagens, vamos destrui-las
    cv::destroyAllWindows();

    // Mats funcionam como ponteiros, muito cuidado com isso.
    cv::Mat pintor = imagem_branca;
    pintor = pintor * 0; // Pinte de preto
    // Isso alterou o conteudo da imagem branca.
    cv::imshow("Imagem branca pintada", imagem_branca);
    cv::waitKey(0);

    // Se voce quer evitar esse efeito colateral, utilize o .clone()
    // Vamos voltar nossa imagem para ser branca novamente
    imagem_branca = imagem_branca + 255;
    // Agora usaremos o clone, isso vai copiar a imagem, porém sem atribuir o
    // ponteiro. Dessa forma podemos mudar `pintor` sem mudar imagem branca
    pintor = imagem_branca.clone();
    pintor = pintor * 0; // Pinte de preto
    // Vamos ver se nossa imagem continua branca
    cv::imshow("Imagem branca", imagem_branca);
    cv::waitKey(0);
    // Ja a imagem `pintor` esta preta
    cv::imshow("Pintor", pintor);
    cv::waitKey(0);

    cv::destroyAllWindows();

    // Existem outras formas de criar Mats
    // Usando o construtor, veja que o tamanho é height, width
    cv::Mat outra_branca(100, 400, CV_8U, cv::Scalar(255.0));
    cv::imshow("Outra branca", outra_branca);
    cv::waitKey(0);
    cv::Mat outra_preta(100, 400, CV_8U, cv::Scalar(0.0));
    cv::imshow("Outra preta", outra_preta);
    cv::waitKey(0);

    // Voce sempre pode fazer um std::cout pra ver o que tem dentro de uma Mat
    cv::Mat matriz_identidade = cv::Mat::eye(4, 4, CV_64F);
    std::cout << "Matriz Identidade: " << matriz_identidade << std::endl;

    cv::destroyAllWindows();

    // Podemos carregar uma imagem de um arquivo com o imread
    cv::Mat pessoa = cv::imread("Aula-01/images/pessoa1.jpeg");
    cv::imshow("Fulano", pessoa);
    cv::waitKey(0);
    // Ok, essa imagem é muito grande, melhor a gente diminuir ela
    cv::Mat pessoa_menor;
    cv::resize(pessoa, pessoa_menor, cv::Size(400, 100));
    cv::imshow("Fulano encolhido", pessoa_menor);
    cv::waitKey(0);
    // Ops, ficou achatado. Melhor fazermos essa redução mantendo a proporção de
    // altura e largura. Que tal reduzirmos pela metade
    cv::resize(pessoa, pessoa_menor, cv::Size(), 0.5, 0.5);
    cv::imshow("Fulano encolhido corretamente", pessoa_menor);
    cv::waitKey(0);
    cv::destroyAllWindows();
    // As vezes queremos a imagem em grayscale. Podemos carregar ela ja em
    // grayscale:
    cv::Mat pessoa_grayscale = cv::imread("Aula-01/images/pessoa1.jpeg", 0);
    cv::imshow("Fulano em grayscale", pessoa_grayscale);
    cv::waitKey(0);
    // Ou converter manualmente:
    cv::cvtColor(pessoa, pessoa_grayscale, CV_BGR2GRAY);
    cv::imshow("Fulano convertido em grayscale", pessoa_grayscale);
    cv::waitKey(0);
    // Podemos salvar essa imagem no disco com o imwrite
    cv::imwrite("Aula-01/images/pessoa1_grayscale.jpeg", pessoa_grayscale);
    cv::destroyAllWindows();

    return 0;
}