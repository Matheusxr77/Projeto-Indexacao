# Projeto de Indexacao em C
![Badge em Desenvolvimento](http://img.shields.io/static/v1?label=STATUS&message=CONCLUIDO&color=dark&style=for-the-badge)

## Tecnologias Utilizadas
<img align="center" alt="Matheusxr77-C" height="50" width="50" src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg">

## Descrição
Códigos referentes ao projeto de indexação de árvores bst, avl e rb para a disciplina de Algoritmos e Estruturas de Dados II da Universidade Federal do Agreste de Pernambuco (UFAPE).

## Instruções
Implemente a lógica interna de funcionamento de um Sistema Gerenciador de Banco de Dados (SGBD), aplicado para gerenciar os dados de apenas uma tabela, utilizando a técnica de indexação, de acordo com as definições a seguir:
+ A tabela deve armazenar registros que contêm pelo menos 5 campos. A definição do registro/campos a serem gerenciados é de livre escolha, desde que seja algo adequado ao ambiente acadêmico.
+ Os campos do tipo string devem ter alocação estática (com tamanho máximo predefinido).
+ Utilize três índices na tabela: um índice BST, um AVL e um RB, cada um em um campo diferente.
+ Os dados dos registros devem ser armazenados em um arquivo binário sequencial, conforme exemplificado no projeto "arquivo 3";
+ Cada índice deve ser salvo em um arquivo próprio, conforme exemplificado no projeto "arquivo 1". OBS: durante a execução do programa, os índices devem ser mantidos em memória RAM, sendo passados para o arquivo apenas quando o usuário escolher a opção "sair" do programa.
+ Implemente a função de adicionar registro, a qual insere o registro no arquivo de dados e atualiza os três índices.
+ Implemente a função de remover registro, que remove apenas as referências ao registro nos índices, sem a necessidade de modificar o arquivo de dados.
+ Implemente uma função de busca para cada índice. Esta função deve imprimir na tela todos os dados satélite do registro referenciado pelo índice passado como parâmetro.
+ Implemente uma função para exibir os registros ordenados de acordo com cada um dos índices (inorder).
+ Implemente a função main que permite ao usuário utilizar o sistema com todas as opções de funções implementadas.