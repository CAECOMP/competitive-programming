import { defineConfig } from 'vitepress'
import themeConfig from './config/themeConfig'
// https://vitepress.dev/reference/site-config
export default defineConfig({
    lang: "pt-BR",
    metaChunk: true,
    appearance: "dark",
    title: "Competitive Programming Handbook",
    description: "De competidores, para competidores.",
    themeConfig
})


