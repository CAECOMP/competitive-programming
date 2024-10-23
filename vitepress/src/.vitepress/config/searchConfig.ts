import { DefaultTheme } from 'vitepress/theme'

const search: { provider: "local", options: DefaultTheme.LocalSearchOptions } =
{
    provider: "local",
    options: {
        locales: {
            root: {
                translations: {
                    button: {
                        buttonText: 'Buscar',
                        buttonAriaLabel: 'Buscar'
                    },
                    modal: {
                        displayDetails: 'Mostrar detalhes',
                        resetButtonTitle: 'Resetar pesquisa',
                        backButtonTitle: 'Voltar',
                        noResultsText: 'Nenhum resultado para ',
                        footer: {
                            selectText: 'para selecionar',
                            navigateText: 'para navegar',
                            closeText: 'para fechar',
                            closeKeyAriaLabel: 'esc'
                        }
                    }
                }
            }
        }
    }
}

export default search
