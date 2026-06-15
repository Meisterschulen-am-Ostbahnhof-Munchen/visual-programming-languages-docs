#set page(
  paper: "a4",
  margin: (top: 2.5cm, bottom: 2.5cm, left: 3cm, right: 2.5cm),
  header: context {
    let elems = query(heading.where(level: 1).before(here()))
    if elems.len() > 0 {
      let current-chapter = elems.last().body
      text(size: 9pt, fill: rgb("#718096"), style: "italic")[
        #current-chapter
        #h(1fr)
        Visuelle Programmiersprachen: Low-Code (4)
      ]
    }
  },
  footer: context {
    let page-num = counter(page).get().first()
    align(center, text(size: 10pt, fill: rgb("#4a5568"))[#page-num])
  }
)

#set text(
  font: ("Liberation Sans", "DejaVu Sans", "Arial"),
  size: 10.5pt,
  lang: "de"
)

#set heading(numbering: "1.1")
#show heading: it => {
  // Add pagebreak before top-level headings (Chapters)
  if it.level == 1 {
    pagebreak(weak: true)
  }
  block(
    above: 1.5em,
    below: 1em,
    it
  )
}

// Title Page
#align(center + horizon)[
  #block(width: 100%, stroke: none, inset: 2cm)[
    #text(size: 32pt, weight: "bold", fill: rgb("#1a3a5f"))[Visuelle Programmiersprachen: Low-Code (4)]
    #v(1.5cm)
    #text(size: 18pt, style: "italic", fill: rgb("#4a5568"))[Referenzhandbuch & Übungsaufgaben]
    #v(3cm)
    #text(size: 14pt, weight: "medium")[Franz Höpfinger]
    #v(0.5cm)
    #text(size: 11pt, fill: rgb("#718096"))[Meisterschulen am Ostbahnhof - München \ 2022-2026]
  ]
]
#pagebreak()

// Table of Contents
#outline(depth: 3, indent: 1.5em)
#pagebreak()

// Include the generated content
#include "book.typ"
