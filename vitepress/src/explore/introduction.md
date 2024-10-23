# Sobre o projeto

Este é um projeto criado pelo CAECOMP - IFCE, com o intuito de distribuir o
conhecimento adquirido da área de programação competitiva com outros programadores.

Esperamos conseguir ajudar e apoiar tanto novatos quanto veteranos, e garantir
medalhas em todo tipo de contest ou hackaton.

<script setup>
import { VPTeamMembers } from 'vitepress/theme'

const members = {
    "Vinícius Menezes": { nick: "ViniciusM2", title: "Presidente do CAECOMP" },
    "Paulo Diego": { nick: "pauloDiego-sudo", title: "Vice-Presidente do CAECOMP" },
    "Claudemir Vieira": { nick: "Claudemirovsky", title: "Desenvolvedor de bugs e dores de cabeça" },
    "Vinicius Castro": { nick: "Vinicius-de-Castro", title: "Designer do CAECOMP" },
    "Caio Cidade": { nick: "CaioCity", title: "Secretário do CAECOMP" }
}
const team = Object.entries(members).map(([k, v]) => {
    return {
        avatar: `https://github.com/${v.nick}.png`,
        name: k,
        title: v.title,
        links: [{ icon: "github", link: `https://github.com/${v.nick}` }]
    }
})
</script>

# Contribuidores

Conheça a equipe por trás deste projeto:

<VPTeamMembers size="small" :members="team" />
