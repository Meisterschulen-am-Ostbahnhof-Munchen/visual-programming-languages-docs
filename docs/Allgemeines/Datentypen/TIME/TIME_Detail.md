# Datentyp-Detail: TIME

```{index} single: Datentyp-Detail: TIME
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
Der Datentyp **TIME** wird zur Darstellung von Zeitdauern (Relativzeit) verwendet.

## Normative Definition
Gemäß **DIN EN 61131-3** (Tabelle 10, Nr. 12a):

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | Meist 32 Bit (Implementierungsabhängig) |
| **Voreingestellter Wert** | `T#0s` |

## Literaldarstellung
TIME-Literale beginnen immer mit dem Präfix `T#` oder `TIME#`. 

### Einheiten
Folgende Einheiten können kombiniert werden (Reihenfolge absteigend):
- `d`: Tage (days)
- `h`: Stunden (hours)
- `m`: Minuten (minutes)
- `s`: Sekunden (seconds)
- `ms`: Millisekunden (milliseconds)

### Syntaxregeln
- Unterstriche (`_`) zur besseren Lesbarkeit sind erlaubt.
- Negative Zeitdauern sind durch ein Minuszeichen nach dem Doppelkreuz möglich (`T#-...`).
- Die Einheiten können gemischt werden (z.B. Tage und Millisekunden).

### Beispiele
- `T#10ms` (10 Millisekunden)
- `T#2h_30m` (2 Stunden und 30 Minuten)
- `T#5d4h3m2s1ms` (Kombination aller Einheiten)
- `TIME#14ms` (Alternative Schreibweise)
- `T#-5s` (Negative Zeitdauer von 5 Sekunden)
- `T#25h_15m` (Überlauf der Einheit ist erlaubt, entspricht 1 Tag, 1 Stunde, 15 Min)