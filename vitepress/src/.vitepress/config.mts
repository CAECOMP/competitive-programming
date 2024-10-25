import { defineConfig } from 'vitepress'
import themeConfig from './config/themeConfig'
import markdown from './config/markdownConfig'
// https://vitepress.dev/reference/site-config
export default defineConfig({
    lang: "pt-BR",
    metaChunk: true,
    base: "/handbook-competitive-programming/",
    appearance: "dark",
    title: "Competitive Programming Handbook",
    description: "De competidores, para competidores.",
    themeConfig,
    markdown
})
