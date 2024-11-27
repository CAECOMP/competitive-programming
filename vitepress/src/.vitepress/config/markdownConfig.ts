import { MarkdownOptions } from "vitepress";
import { tabsMarkdownPlugin } from 'vitepress-plugin-tabs'

const markdown: MarkdownOptions = {
    image: {
        lazyLoading: true
    },
    math: true,
    lineNumbers: true,
    config: (markdown) => {
        markdown.use(tabsMarkdownPlugin)
    }
}

export default markdown
