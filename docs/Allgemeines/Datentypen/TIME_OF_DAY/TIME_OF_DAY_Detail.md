# Datentyp-Detail: TIME_OF_DAY (TOD)

```{index} single: Datentyp-Detail: TIME_OF_DAY (TOD)
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
Der Datentyp **TIME_OF_DAY** (kurz **TOD**) wird zur Darstellung der Tageszeit verwendet.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 14a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | Meist 32 Bit (Implementierungsabhängig) |
| **Voreingestellter Wert** | `TOD#00:00:00` |

## Literaldarstellung
Literale beginnen mit dem Präfix `TOD#` oder `TIME_OF_DAY#`. Das Format folgt dem Schema `hh:mm:ss.ss`.

### Beispiele
- `TOD#15:36:55.36`
- `TIME_OF_DAY#08:00:00`
- `tod#23:59:59.999`