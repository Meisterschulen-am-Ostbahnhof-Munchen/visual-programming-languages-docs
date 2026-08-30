# AD_TO_AR_NUM

![AD_TO_AR_NUM](./AD_TO_AR_NUM.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AD_TO_AR_NUM** ist die numerisch korrekte Alternative zu [`AD_TO_AR`](./AD_TO_AR.md): Er wandelt einen DWORD-Wert aus einem unidirektionalen AD-Adapter (Socket) über einen internen UDINT-Zwischenschritt in einen REAL-Wert um, der über einen AR-Adapter (Plug) ausgegeben wird — eine **echte Wertumwandlung**, keine Bit-Reinterpretation.

## Warum nicht einfach AD_TO_AR?

`AD_TO_AR` nutzt intern `F_DWORD_TO_REAL`, was im FORTE-Kern für Bit-String-Quelltypen (BYTE/WORD/DWORD/LWORD) eine reine IEEE754-Bit-Reinterpretation ist, keinen numerischen Cast. Ein roher Zähler- oder Analogwert wie `DWORD#2048` würde dadurch **nicht** zu `REAL#2048.0`, sondern zu einer bedeutungslosen Zahl nahe Null (siehe [`AD_TO_AR`](./AD_TO_AR.md) und `AD_TO_AR_TODO.md` für die Herleitung).

## Schnittstellenstruktur

Der Baustein besitzt keine direkten (einzelnen) Ereignis- oder Daten-Ein-/Ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter-Schnittstellen:

### **Adapter**

| Name   | Typ                                       | Richtung | Beschreibung                                                                 |
|--------|--------------------------------------------|----------|-----------------------------------------------------------------------------|
| AD_IN  | `adapter::types::unidirectional::AD`      | Socket   | Empfängt ein Ereignis (E1) und einen DWORD-Rohwert (D1) zur Konvertierung. |
| AR_OUT | `adapter::types::unidirectional::AR`      | Plug     | Sendet ein Ereignis (E1) mit dem numerisch umgewandelten REAL-Wert (D1) aus. |

## Funktionsweise

Der Baustein arbeitet zweistufig statt in einem einzigen (gefährlichen) Schritt:

1. Ein eingehendes Ereignis am Socket **AD_IN.E1** triggert die Konvertierung.
2. Der Datenwert **AD_IN.D1** (DWORD) wird an `ToUDINT` (`F_DWORD_TO_UDINT`) übergeben — eine Bit-Reinterpretation DWORD→UDINT, die hier **gültig** ist, da beide Typen dieselbe 32-Bit-Darstellung eines vorzeichenlosen Integers teilen.
3. `ToUDINT.CNF` löst `ToREAL` (`F_UDINT_TO_REAL`) aus — ein **echter numerischer Cast**, der den UDINT-Zahlenwert korrekt in REAL überführt.
4. Das Ergebnis wird über den Plug **AR_OUT.E1**/**AR_OUT.D1** ausgegeben.

## Technische Besonderheiten

- **Identische Schnittstelle wie `AD_TO_AR`**: `AD_TO_AR_NUM` ist ein Drop-in-Ersatz — gleiche Socket-/Plug-Typen (`AD`/`AR`), einfach austauschbar, sobald klar ist, dass ein Zahlenwert (nicht ein Bitmuster) gemeint ist.
- **Zweistufige Kette DWORD→UDINT→REAL**: Dieselbe Kette, die bereits in mehreren Übungen (`Uebung_028a_AR` u. a.) von Hand verdrahtet wird, hier als ein einziger Baustein.
- **Kein Genauigkeitsverlust im relevanten Wertebereich**: `UDINT` (32 bit, max. 4.294.967.295) wird verlustfrei in `REAL` (IEEE754 einfache Genauigkeit, 24-Bit-Mantisse) übertragen, solange der Wert innerhalb der exakt darstellbaren Ganzzahlen liegt (bis 2²⁴ = 16.777.216) — für typische Analog-/Zählerrohwerte (z. B. 0–64255 oder 0–4095) unproblematisch.

## Anwendungsszenarien

- **Analoge Rohwerte**: Ein Analogeingang oder Zähler liefert einen DWORD-Rohwert (z. B. 0–4095, 0–64255), der als tatsächlicher Zahlenwert in REAL weiterverarbeitet werden soll (Skalierung, Anzeige, OPC-UA-Publish).
- **Ersatz für die manuelle `AD_TO_AUDI` + `AUDI_TO_AR`-Kette**: Wo bisher zwei separate Adapter-Instanzen im SubApp-Netzwerk nötig waren, genügt jetzt eine.

## Vergleich mit ähnlichen Bausteinen

- **[`AD_TO_AR`](./AD_TO_AR.md)**: die Bit-Reinterpretations-Variante — nur verwenden, wenn `AD_IN` bereits ein Bitmuster ist, das als REAL interpretiert werden soll.
- **`AI_TO_AR`/`ADI_TO_AR`/`AUDI_TO_AR`**: bereits numerisch korrekt, da ihre Quelltypen `ANY_INT` sind — falls der Rohwert bereits als INT/DINT/UDINT-Adapter vorliegt, ist keine `_NUM`-Variante nötig.

## Fazit

**AD_TO_AR_NUM** schließt die Lücke zwischen dem naheliegenden, aber gefährlichen `AD_TO_AR` und der tatsächlich benötigten numerischen DWORD→REAL-Umwandlung — als einzelner, drop-in-kompatibler Baustein statt einer manuell verdrahteten Zwei-Baustein-Kette.

---

### 📖 Hintergrund

* [Numerisch vs. bitweise: Die Konvertierungs-Falle in FORTE](../Numerisch_vs_Bitweise.md)

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
