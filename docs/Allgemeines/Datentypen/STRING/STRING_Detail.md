# Datentyp-Detail: STRING

```{index} single: Datentyp-Detail: STRING
```

## 🎧 Podcast

* [Datenkommunikation in der Automatisierung: Die Geheimnisse der IEC 61499 Datentypen](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datenkommunikation-in-der-Automatisierung-Die-Geheimnisse-der-IEC-61499-Datentypen-e3672lj)
* [Datentypen der IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datentypen-der-IEC-61499-e3672jf)
* [SINT, INT, DINT: Warum die Wahl des Datentyps über Effizienz und Fehler entscheidet](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/SINT--INT--DINT-Warum-die-Wahl-des-Datentyps-ber-Effizienz-und-Fehler-entscheidet-e3673b8)
* [Universum der Datentypen, wie sie in der IEC 61131-3 und IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Universum-der-Datentypen--wie-sie-in-der-IEC-61131-3-und-IEC-61499-e3673kb)
* [Analyse der Novellierung der Meisterprüfungsverordnung im Land- und Baumaschinenmechatroniker-Handwerk: Ein Detaillierter Vergleich der Verordnungen von 2024 und 2001](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Analyse-der-Novellierung-der-Meisterprfungsverordnung-im-Land--und-Baumaschinenmechatroniker-Handwerk-Ein-Detaillierter-Vergleich-der-Verordnungen-von-2024-und-2001-e37aejv)

## 📺 Video

* [Das Relais im Detail: Schaltverstärker, Schutz und die Geheimnisse von A1/A2, 85/86 und der Hyste...](https://www.youtube.com/watch?v=OUNlE4NABX4)
* [MOTIX™ BTM9020EP im Detail](https://www.youtube.com/watch?v=A0-osdslKYE)
* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Beschreibung
Der Datentyp **STRING** repräsentiert eine Zeichenfolge, die aus 8-Bit-Zeichen (üblicherweise ISO/IEC 10646-1 oder ASCII) besteht.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 16a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 8 Bit pro Zeichen |
| **Voreingestellter Wert** | '' (leere Zeichenfolge) |
| **Maximale Länge** | Herstellerspezifisch (Standard oft 255) |

## Literaldarstellung
Zeichenfolge-Literale werden in **einfache Anführungszeichen** (`'`) eingeschlossen.

### Sonderzeichen (Escape-Sequenzen)
Sonderzeichen werden durch ein Dollar-Zeichen (`$`) eingeleitet:

| Sequenz | Bedeutung |
| :--- | :--- |
| `$$` | Dollar-Zeichen |
| `$'` | Einfaches Anführungszeichen |
| `$L` oder `$l` | Zeilenvorschub (Line Feed) |
| `$N` oder `$n` | Neue Zeile (Newline) |
| `$P` oder `$p` | Seitenvorschub (Page Feed) |
| `$R` oder `$r` | Wagenrücklauf (Carriage Return) |
| `$T` oder `$t` | Tabulator |
| `$hh` | Zeichen mit Hex-Code `hh` (z.B. `$41` für 'A') |

### Beispiele
- `'Hallo Welt'` (Einfacher Text)
- `'Zeile 1$NZeile 2'` (Mit Zeilenumbruch)
- `'Zahl: $R$L100'` (Wagenrücklauf und Zeilenvorschub)
- `'STRING#''Abc'''` (Mit explizitem Typ-Präfix)