# SwitchPic(Col)-Bausteine: Gemeinsames Muster

* * * * * * * * * *

## Einleitung

`MyLib::sys` (test_B) enthält eine Familie von Bausteinen, die **je nach Zustand ein anderes VT-Bild (Object-Pointer-Ziel) und/oder eine andere Hintergrundfarbe anzeigen** — z. B. eine Schieber-/Ventilanimation mit den Zuständen Unknown/Closed/Opening/Opened/Closing. Diese Seite erklärt das gemeinsame Muster; die Einzelseiten nennen nur die konkreten Abweichungen.

## Namensschema

`SwitchPic[Col]_<Zustände>_<Variante>[_aux]`

| Bestandteil | Bedeutung |
|---|---|
| **`Col`** (optional) | Schaltet zusätzlich zum Bild auch eine Hintergrundfarbe (`Q_BackgroundColour`) passend zum Zustand um, nicht nur ein Bild (`Q_NumericValue`). |
| **Zustände** (`2` oder `5`) | `2` = boolescher Selector `DI1` (`up`/`down`, Typ `s2x1ObjectIDs`/`s2x2ObjectIDs`); `5` = `iSTATE`-Selector (`USINT`, Schieber-Zustandsautomat Unknown/Closed/Opening/Opened/Closing, Typ `SchieberStruct`/`SchieberAuxInStruct`), ausgewertet über `F_MUX_5`. |
| **Variante** (`1`/`2`/`3`, nur bei `SwitchPic`) | Anzahl/Art der gleichzeitig aktualisierten VT-Objekte: `1`=nur normales VT-Objekt (Softkey/DataMask), `2`=zusätzlich AUX-Objekt, `3`=zusätzlich AUX-Objekt UND ein zweites normales Objekt ("Button"). |
| **`_aux`** | Nur AUX-Objekt(e) werden geschaltet, kein normales VT-Objekt (Gegenstück zu Variante `1`, aber ausschließlich für Auxiliary-Function-Objekte). |

## Funktionsweise

1. Eine Struktur `pictures`/`Sets` (Typ abhängig von Zuständen/Variante) enthält für jeden möglichen Zustand die zugehörige(n) Object-ID(s) (Bild und ggf. Farbe).
2. `F_MOVE` entpackt diese Struktur in Einzelwerte.
3. Ein Multiplexer (`F_SEL` bei 2 Zuständen, `F_MUX_5` bei 5 Zuständen, gesteuert über `DI1` bzw. `iSTATE`) wählt die zum aktuellen Zustand passenden Werte aus.
4. `Q_NumericValue`/`Q_NumericValueAux` setzt den gewählten Object-Pointer-Wert auf das per `Picture`/`PictureA`/`PictureB` identifizierte VT-Objekt; bei `Col`-Varianten setzt zusätzlich `Q_BackgroundColour`/`Q_BackgroundColourAux` die Hintergrundfarbe auf das per `Color` identifizierte Objekt.
5. Bei mehreren Zielobjekten (Variante 2/3) werden mehrere `Q_NumericValue(Aux)`-Instanzen in einer festen INIT-Kette hintereinandergeschaltet (jede löst per `INITO` die nächste aus), bevor `INITO` nach außen gemeldet wird.

## Zusammenfassung

Ein Multiplexer-Muster: Zustand → Struktur-Lookup (`F_MOVE`) → Auswahl (`F_SEL`/`F_MUX_5`) → ein oder mehrere `Q_NumericValue(Aux)`/`Q_BackgroundColour(Aux)`-Ziele. Die Variantenzahl (1/2/3) und `Col`/`_aux` bestimmen nur, wie viele Ziele mit welchem Typ (normal/AUX, Bild/Farbe) gleichzeitig aktualisiert werden.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
