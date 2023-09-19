
// Função de callback para escrever os dados recebidos pela requisição
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string curl_pegabloco(std::string url_,std::string parametros){
    // Inicialização do libcurl
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    std::string resultado="";
    if (curl) {
        // URL do endpoint para onde será enviada a requisição POST
        std::string url = url_;
        
        // Dados que serão enviados no corpo da requisição POST
        std::string postData = parametros;
        
        // Configuração da requisição cURL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        
        // Armazena a resposta recebida em uma string
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        // Executa a requisição
        res = curl_easy_perform(curl);
        
        // Verifica se a requisição foi bem-sucedida
        if (res != CURLE_OK) {
            //ERRO NA REQUISICAO
            resultado= "0";
            
        } else {
            // esta tudo serto
            resultado= response;
        }
        
        // Limpa a instância do cURL e libera recursos
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Falha na inicialização do cURL." << std::endl;
    }
    return resultado;
}
