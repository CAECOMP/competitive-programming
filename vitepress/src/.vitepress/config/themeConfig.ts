import type { DefaultTheme } from 'vitepress'

import sidebar from './navigation/sidebar'
import search from './searchConfig'

const themeConfig: DefaultTheme.Config = {
    // https://vitepress.dev/reference/default-theme-config
    logo: "/caecomp.png",
    siteTitle: false,
    search,
    nav: [
        { text: 'Explorar', link: '/explore/guide' }
    ],
    sidebar,
    socialLinks: [
        { icon: 'github', link: 'https://github.com/CAECOMP' }
    ],
    darkModeSwitchTitle: "Usar o tema escuro",
    lightModeSwitchTitle: "Usar o tema claro",
    docFooter: {
        prev: 'Página anterior',
        next: 'Próxima página'
    },
    outline: {
        label: "Conteúdo"
    }
}

export default themeConfig
