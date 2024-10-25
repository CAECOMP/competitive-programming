import { Printer } from "@web-printer/core"
import vitepress from "@web-printer/vitepress"

import type { MaybeMultiURL, Plugin } from "@web-printer/core"

function plugin(options: { url: MaybeMultiURL, base: string }): Plugin {
    const orig = vitepress(options)
    orig.injectStyle = () => {
        return {
            contentSelector: "content",
            avoidBreakSelector: ".custom-block"
        }

    }
    orig.onPageWillPrint = async ({ page, pageInfo }) => {
        if (pageInfo.url.endsWith("/library/")) {
            const elem = page.locator("div.custom-block a[href]")
            await elem.evaluate((item, base: string) => {
                item.setAttribute("href", base + item.getAttribute("href"))
            }, base)
        }
    }
    return orig
}

const url = "http://localhost:4173/handbook-competitive-programming/library/"
const owner = (process.env.GITHUB_REPOSITORY_OWNER ?? "caecomp").toLowerCase()
const base = `https://${owner}.github.io`

new Printer({ threads: 16, outputDir: __dirname + "/.vitepress/dist/" })
    .use(plugin({ url, base }))
    .print("Biblioteca", {
        filter: ({ url }) => url.includes("/library/"),
        continuous: true,
        replaceLink: true,
        printBackground: true,
        format: "A4",
        margin: { left: 0, right: 0 },
        style: `
            @media print {
            .VPNav,
            .VPLocalNav,
            .VPDocFooter {
                    display: none!important;
                }
            }`
    })
