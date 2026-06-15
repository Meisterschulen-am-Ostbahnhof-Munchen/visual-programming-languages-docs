#import "@preview/orange-book:0.7.1": book

#let horizontalrule = line(length: 100%, stroke: 0.5pt + luma(150))

#show: book.with(
  title: "Visuelle Programmiersprachen: Low-Code (4)",
  subtitle: "Referenzhandbuch & Übungsaufgaben",
  author: "Franz Höpfinger",
  date: "2022-2026",
  paper-size: "a4",
  copyright: [2022-2026, Meisterschulen am Ostbahnhof - München],
  lang: "de",
  main-color: rgb("#F36619"), // Das typische Orange-Book Orange
)

#include "book.typ"
