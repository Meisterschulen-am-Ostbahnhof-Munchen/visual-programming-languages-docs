# E_REND_3

* * * * * * * * * *

## Einleitung

Der `E_REND_3` ist die generische 3-Eingangs-Variante des Rendezvous-Bausteins `E_REND` (2 Eingänge). Er löst `EO` erst aus, wenn er von **allen** 3 Eingängen (`EI1`, `EI2`, `EI3`) mindestens ein Ereignis seit dem letzten Reset empfangen hat — eine logische UND-Verknüpfung über 3 asynchrone Ereignisströme.

![E_REND_3](E_REND_3.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **EI1**: Ereigniseingang 1.
- **EI2**: Ereigniseingang 2.
- **EI3**: Ereigniseingang 3.
- **R (Reset)**: Setzt den Baustein in seinen Anfangszustand zurück, verwirft alle bisher gemerkten Ereignisse.

### **Ereignis-Ausgänge**

- **EO**: Wird ausgelöst, sobald alle 3 Eingänge seit dem letzten Reset mindestens einmal ausgelöst wurden.

## Funktionsweise

`E_REND_3` ist als generischer Funktionsbaustein implementiert (`eclipse4diac::core::GenericClassName = 'GEN_E_REND'`) — dieselbe C++-Implementierung liegt allen `E_REND_n`-Varianten zugrunde, nur die Anzahl der Eingänge unterscheidet sich. Intern merkt sich der Baustein, welche der `EI1`…`EI3`-Eingänge bereits mindestens ein Ereignis erhalten haben. Sobald alle 3 Eingänge markiert sind, wird `EO` ausgelöst und der interne Merker zurückgesetzt. Ein `R`-Ereignis setzt den Merker jederzeit zurück, ohne `EO` auszulösen.

## Technische Besonderheiten

- **Generische Implementierung**: Wie `E_REND` (2 Eingänge) selbst basiert `E_REND_3` auf derselben generischen `GEN_E_REND`-C++-Klasse; die Eingangsanzahl wird zur Übersetzungszeit über die Typdefinition festgelegt.
- **Reihenfolgeunabhängig**: Die Eingänge `EI1`, `EI2`, `EI3` müssen nicht in einer bestimmten Reihenfolge eintreffen.
- **Automatischer Reset nach Auslösung**: Nach jedem `EO` beginnt der Baustein wieder von vorn.

## Zustandsübersicht

Der Baustein merkt sich intern eine Bitmaske der bereits eingetroffenen Eingänge; bei vollständiger Maske wird `EO` ausgelöst und die Maske geleert.

## Anwendungsszenarien

- **Synchronisation von 3 unabhängigen Vorbedingungen**, bevor ein Folgeschritt ausgelöst wird (z. B. 3 Sensoren müssen alle ausgelöst haben, bevor eine Anlage weiterläuft).
- **Erweiterung von `E_REND`** auf mehr als zwei Ereignisquellen, ohne mehrere `E_REND`-Bausteine kaskadieren zu müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_REND`**: die 2-Eingangs-Basisvariante.
- `E_REND_2`, `E_REND_4`: dieselbe generische Implementierung mit einer anderen Eingangsanzahl.
- **`E_MERGE_3`**: die logische ODER-Verknüpfung mehrerer Ereigniseingänge (feuert bei jedem einzelnen Ereignis statt erst nach allen).

## Fazit

`E_REND_3` erweitert das Rendezvous-Prinzip von `E_REND` auf 3 gleichzeitig zu synchronisierende Ereignisströme und ist die generische, für 3 Eingänge instanziierte Variante derselben zugrunde liegenden Implementierung.
