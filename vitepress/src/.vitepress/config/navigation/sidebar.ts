
import type { DefaultTheme } from 'vitepress'

const sidebar: DefaultTheme.SidebarItem[] = [
    {
        text: "Explorar",
        base: "/explore/",
        items: sidebarExplore()
    },
    {
        text: "Biblioteca",
        base: "/library/",
        items: sidebarLibrary()
    },
    {
        text: "Por trás dos panos",
        base: "/learn/",
        items: sidebarLearn(),
    },
    {
        text: "Dicas e paranauês",
        base: "/tips/",
        items: sidebarTips()
    }

]

function sidebarExplore(): DefaultTheme.SidebarItem[] {
    return [
        { text: "Introdução", link: "introduction" },
        { text: "Guia", link: "guide" }
    ]

}

function sidebarLibrary(): DefaultTheme.SidebarItem[] {
    return [
        {
            text: "Programação dinâmica",
            base: "/library/dp/",
            items: [{ text: "Problema da mochila", link: "knapsack" }]
        },
        {
            text: "Estruturas", base: "/library/structures/", items: [
                { text: "Disjoint set union (UnionFind)", link: "dsu" },
                { text: "Segtrees", link: "segtrees" }
            ]
        },
        {
            text: "Grafos", base: "/library/graphs/", items: [
                { text: "Detecção de ciclo", link: "cycle-detection" },
                { text: "Menor caminho", link: "shortest-path" }
            ]
        }
    ]

}

function sidebarLearn(): DefaultTheme.SidebarItem[] {
    return [
        { text: "Segtrees", base: "/", link: "TODO" }
    ]
}

function sidebarTips(): DefaultTheme.SidebarItem[] {
    return [
        { text: "Dicas de debug", base: "/", link: "TODO" }
    ]
}

export default sidebar
