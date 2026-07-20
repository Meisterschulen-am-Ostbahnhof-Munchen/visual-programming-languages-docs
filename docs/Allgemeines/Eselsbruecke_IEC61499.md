# Eselsbrücke: IEC 61499

Wie merkt man sich zuverlässig die Nummer der Norm **IEC 61499** (Function Blocks
for Industrial-Process Measurement and Control Systems) – der Norm, auf der
4diac/FORTE und damit dieses ganze Projekt aufbaut?

Antwort: mit einem Traktor.

## Die Eselsbrücke in einem Satz

> **Case IH 1455** – kennt jeder. Ein 6-Zylinder-Traktor. Die **6** und die
> **14** hat man damit schon im Kopf. Jetzt muss man nur noch aus der **55**
> eine **99** machen – fertig ist die **61499**.

## Schritt für Schritt

| Baustein | Herkunft | Ergebnis |
|---|---|---|
| **6** | Case IH 1455 ist ein **6-Zylinder**-Traktor | `6 _ _ _ _` |
| **14** | Die ersten beiden Ziffern von **14**55 | `6 1 4 _ _` |
| **99** | Aus der **55** am Ende von 1455 wird eine **99** | `6 1 4 9 9` |

Zusammengesetzt ergibt das: **6 · 14 · 99 → 61499**

## Der Trick mit der 55 → 99

Der einzige Schritt, der nicht "geschenkt" ist, ist die Umwandlung der
Endziffern **55 → 99**. Zwei Bilder, die dafür helfen können:

- **Rechnerisch:** 55 + 44 = 99 (die "44" kann man sich als PS-Aufrundung des
  Traktors vorstellen, wenn das hilft).
- **Bildlich:** Die beiden Fünfen des Traktor-Typs "wachsen" im Kopf zu zwei
  Neunen heran – aus `1455` wird gedanklich `1499`.

Wichtig ist nur, dass am Ende hängen bleibt: **die letzten beiden Ziffern der
Norm sind NICHT 55, sondern 99.**

Schade eigentlich: Das IHC-Werk wurde 1997 geschlossen – wäre es erst 1999
geschlossen worden, ließe sich die **99** direkt aus dem Schließungsjahr
herleiten, statt sie sich künstlich aus der 55 zurechtbiegen zu müssen.

## Die komplette Merkkette

1. Ich denke an einen **Case IH 1455**.
2. Der hat **6 Zylinder** → erste Ziffer: **6**
3. Der Rest des Typnamens beginnt mit **14** → nächste Ziffern: **1**, **4**
4. Die **55** am Ende wird zur **99** → letzte Ziffern: **9**, **9**
5. Zusammen: **6 – 1 – 4 – 9 – 9** = **IEC 61499**

## Warum das funktioniert

Eselsbrücken funktionieren am besten, wenn sie ein abstraktes Faktum (eine
5-stellige Normnummer) an ein konkretes, bildhaftes und emotional verankertes
Wissen koppeln (einen bekannten Traktor). Der Case IH 1455 ist genau so ein
Anker: leicht vorstellbar, unverwechselbar, und liefert sogar von sich aus
schon drei der fünf Ziffern (1, 4, 5) plus ein zusätzliches Fakt (6 Zylinder)
frei Haus. Der einzige "künstliche" Schritt – 55 wird zu 99 – ist bewusst
klein gehalten, damit die Brücke nicht zu wackelig wird.

## Kurzfassung zum Auswendiglernen

> **Case IH 1455, 6 Zylinder. Aus der 55 mach eine 99. IEC 61499.**

## Weiterführender Link

* [Traktorenlexikon: Case-IH 1455 XL – Wikibooks](https://de.wikibooks.org/wiki/Traktorenlexikon:_Case-IH_1455XL)
* [Traktorenlexikon: IHC 1455 XL – Wikibooks](https://de.wikibooks.org/wiki/Traktorenlexikon:_IHC_1455XL)
