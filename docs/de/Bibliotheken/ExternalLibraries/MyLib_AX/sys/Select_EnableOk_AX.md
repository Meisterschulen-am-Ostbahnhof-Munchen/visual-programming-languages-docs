# Select_EnableOk_AX

![Select_EnableOk_AX_network](./Select_EnableOk_AX_network.svg)

* * * * * * * * * *

## Einleitung

`Select_EnableOk_AX` ist die adapter-native Variante von `Select_EnableOk`: `bEnable`/`bOk` kommen als AX-Adapter (statt Klartext-BOOL), `value` geht als AUS-Adapter raus. Kein Event-Handling noetig - jede Aenderung an `bEnable`/`bOk` propagiert automatisch ueber die Adapter-Kette.

## Verwendete Funktionsbausteine (FBs)

- **initval_AUS_DISABLED / initval_AUS_OK / initval_AUS_FAULT** (`adapter::types::unidirectional::AUS::initval::initval_AUS`): speisen die 3 Parameter-Werte (`valDisabled`/`valOk`/`valFault`) als AUS-Adapter ein, einmalig bei Instanziierung.
- **F_SEL_OK_FAULT** (`adapter::iec61131::selection::AUS_AX_SEL_AUS`): waehlt zwischen Fault/Ok-Adapter nach `bOk` (Adapter-Gate statt Event-Selektor).
- **F_SEL_ENABLE** (`adapter::iec61131::selection::AUS_AX_SEL_AUS`): waehlt zwischen Disabled-Adapter/Zwischenergebnis nach `bEnable`.

## Technische Besonderheiten

- 2-stufig wie die Event-Variante `Select_EnableOk`, aber ohne `REQ`/`CNF` auf dieser Ebene - die Adapter-Verbindungen selbst propagieren jede Aenderung.

## Zusammenfassung

Vollstaendig adapter-native Variante von [`Select_EnableOk`](../../MyLib_B/sys/Select_EnableOk.md), passend zur GreenBlueBackground1_AX/GreenRedBackground1_AX-Familie.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
