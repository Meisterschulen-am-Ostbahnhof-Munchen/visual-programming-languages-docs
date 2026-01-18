# Datentyp-Detail: QUARTER

```{index} single: Datentyp-Detail: QUARTER
```

## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
* [Das Geheimnis des 2-Bit-Quarter: Effizienz im CAN-Bus für Nutzfahrzeuge](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Das-Geheimnis-des-2-Bit-Quarter-Effizienz-im-CAN-Bus-fr-Nutzfahrzeuge-e3673bk)
* [Datenkommunikation in der Automatisierung: Die Geheimnisse der IEC 61499 Datentypen](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datenkommunikation-in-der-Automatisierung-Die-Geheimnisse-der-IEC-61499-Datentypen-e3672lj)
* [Datentypen der IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datentypen-der-IEC-61499-e3672jf)
* [SINT, INT, DINT: Warum die Wahl des Datentyps über Effizienz und Fehler entscheidet](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/SINT--INT--DINT-Warum-die-Wahl-des-Datentyps-ber-Effizienz-und-Fehler-entscheidet-e3673b8)

## 📺 Video

* [Das Relais im Detail: Schaltverstärker, Schutz und die Geheimnisse von A1/A2, 85/86 und der Hyste...](https://www.youtube.com/watch?v=OUNlE4NABX4)
* [MOTIX™ BTM9020EP im Detail](https://www.youtube.com/watch?v=A0-osdslKYE)
* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Beschreibung
Der Datentyp **QUARTER** ist ein 2-Bit Datentyp, der vier Zustände repräsentiert. Er ist nicht normativ in der IEC 61131-3 oder IEC 61499 verankert, sondern lehnt sich an Definitionen aus der **SAE J1939** bzw. **ISO 11783-6** (ISOBUS) an.

## Definition und Wertebereich

| Eigenschaft | Wert |
| :--- | :--- |
| **Bits** | 2 |
| **Anzahl Zustände** | 4 |

### Standard-Zustandsdefinition (angelehnt an SAE J1939)

| Binärwert | Dezimal | Bedeutung (Typisch) |
| :--- | :--- | :--- |
| `00` | 0 | **Aus / OFF** |
| `01` | 1 | **Ein / ON** |
| `10` | 2 | **Fehler / Error** (oder Reserved) |
| `11` | 3 | **Nicht verfügbar / Not Available** (oder Don't Care) |

## Verwendung
Dieser Datentyp wird häufig zur effizienten Übertragung von Zustandsinformationen verwendet, bei denen neben dem reinen Schaltzustand (Ein/Aus) auch Diagnoseinformationen (Fehler, Nicht Verfügbar) relevant sind.

## Hinweise
Da **QUARTER** kein Standard-Datentyp der IEC-Normen ist, wird er in Programmierumgebungen oft als `BYTE` oder `USINT` abgebildet, wobei nur die unteren 2 Bits relevant sind oder mehrere QUARTER-Werte in ein Byte gepackt werden (Packing).