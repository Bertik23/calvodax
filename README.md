# Calvodax

Calvodax is a calculator, that can represent numbers with unlimited precision.

## Usage
Run using 
```sh
./calvodax
```
Export variables with 
```
export filename
```
Import variables with 
```
import filename
```
Perform basic operations with standard math notation (you have to add spaces between tokens)
You can use functions like this 
```
factorial ( number )
round ( number )
floor ( number )
ceil ( number )
```



# Zadání

|                                                 |
|-------------------------------------------------|
| **Aplikace: Kalkulačka s neomezenou přesností** |

<table id="maintable" width="100%" data-border="0" data-cellspacing="0"
data-cellpadding="2">
<tbody>
<tr class="odd">
<td class="ltCell" style="text-align: left;"><strong>Termín
odevzdání:</strong></td>
<td class="tCell" style="text-align: left;"><strong>12.06.2023
11:59:59</strong></td>
</tr>
<tr class="even">
<td class="lCell"
style="text-align: left;"><strong>Hodnocení:</strong></td>
<td colspan="2" class="rCell"
style="text-align: left;"><strong>0.0000</strong></td>
</tr>
<tr class="odd">
<td class="lCell" style="text-align: left;"><strong>Max.
hodnocení:</strong></td>
<td colspan="2" class="rCell"
style="text-align: left;"><strong>12.0000</strong> (bez bonusů)</td>
</tr>
<tr class="even">
<td class="lCell" style="text-align: left;"><strong>Odevzdaná
řešení:</strong></td>
<td colspan="2" class="rCell" style="text-align: left;">0 / 20</td>
</tr>
<tr class="odd">
<td class="lbCell"
style="text-align: left;"><strong>Nápovědy:</strong></td>
<td colspan="2" class="rbCell" style="text-align: left;">0 / 5</td>
</tr>
<tr class="even">
<td colspan="3" class="lrtbCell" style="text-align: left;"><div
class="paragraph">
<p><em>Tato semestrální práce patří do kategorie <strong>interaktivních
aplikací</strong>. Vaším cílem je vytvořit aplikaci, kterou bude
uživatel interaktivně ovládat (např. pomocí příkazů na standardním
vstupu). Případné parametry aplikace se nesnažte definovat přímo v kódu
(a to ani pomocí konstant). Umístěte je do konfiguračních souborů
(jednoho nebo více), které váš program bude načítat.</em></p>
</div>
<div class="paragraph">
<p>Vaším úkolem je vytvořit kalkulačku pro výpočty s neomezenou
přesností. Jednotlivá čísla a výsledky operací je možné ukládat do
proměnných a tyto proměnné následně využívat v dalších výpočtech.</p>
</div>
<div class="paragraph">
<p>Kalkulačka musí implementovat následující funkcionality:</p>
</div>
<div class="olist arabic">
<ol>
<li><p>Práce s celými i desetinnými čísly (především načtení a vypsání
proměnných).</p></li>
<li><p>Základní operace: sčítání, odčítání, násobení.</p></li>
<li><p>Pro celá čísla implementujte navíc celočíselné dělení a zbytek po
dělení.</p></li>
<li><p>Funkce pro zaokrouhlení, faktoriál a umocňování (exponent je celé
nezáporné číslo).</p></li>
<li><p>Stav kalkulačky (tedy její proměnné) je možné uložit do souboru v
textově čitelné formě. Stejně tak je potom možné tento stav ze souboru
obnovit.</p></li>
<li><p>Uložení v rámci proměnných (a souboru) musí být paměťově
efektivní. Při ukládání proměnné do paměti se musí určit typ daného
čísla. Rozlišujte alespoň řídká čísla (obsahují především nulové
hodnoty, př. 10^10) a hustá čísla (opak řídkých, př. 100! / 10^20) a
podle toho určete efektivní reprezentaci.</p></li>
</ol>
</div>
<div class="paragraph">
<p>Dále aplikace musí zpracovávat výrazy dle jednoho z následujících
principů:</p>
</div>
<div class="olist arabic">
<ol>
<li><p>Základní operace (alespoň sčítání, odčítání a násobení) musí jít
vnořovat pomocí závorek (př. <code>(3 + X) * Y</code>), závorky mohou
být libovolně vnořené. Funkce a složitější operace mohou fungovat formou
individuálních příkazů bez dalšího skládání (př.
<code>A = ROUND X -5</code>).</p></li>
<li><p>Pro zapisování výrazů využijte prefixový (nebo postfixový) zápis,
mají tu výhodu, že nevyžadují závorky a snáze se zpracovávají. V tomto
případě však veškeré operace a funkce musí jít zapsat v jednom výrazu
(př. <code>A = ROUND MUL Y ADD 3 X -5</code>).</p></li>
</ol>
</div>
<div class="paragraph">
<p>Ukázka běhu programu: <em>(nezávazný příklad)</em></p>
</div>
<div class="listingblock">
<div class="content">
<pre class="highlight"><code>IMPORT memory.calc
X = FACT 100
SCAN Y
// input from user …
Z = X / Y^20
A = ROUND Z 10
PRINT A
EXPORT memory.calc</code></pre>
</div>
</div>
<div class="paragraph">
<p>Kde lze využít polymorfismus? <em>(doporučené)</em></p>
</div>
<div class="ulist">
<ul>
<li><p>reprezentace čísel: řídká čísla, hustá čísla, …</p></li>
<li><p>operace: sčítání, odčítání, násobení, …</p></li>
<li><p>formáty exportu: textový, binární, …</p></li>
<li><p>uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé
varianty), …</p></li>
</ul>
</div>
<div class="paragraph">
<p>Další informace:</p>
</div>
<div class="ulist">
<ul>
<li><p>Pro parsování výrazu se může hodit Shunting-Yard algoritmus (<a
href="http://en.wikipedia.org/wiki/Shunting-yard_algorithm"
class="bare">http://en.wikipedia.org/wiki/Shunting-yard_algorithm</a>).</p></li>
<li><p>Pro uložení do souboru můžete využít i binární formát, v takovém
případě dejte uživateli na výběr.</p></li>
<li><p>Nesnažte se ukládat čísla do textového řetězce, taková
reprezentace je velice neefektivní.</p></li>
</ul>
</div></td>
</tr>
<tr class="odd">
<td colspan="3" class="lrtCell" style="text-align: left;">Tato úloha je
hodnocena automatem a následně vyučujícím. Nejprve úlohu odevzdejte a
odlaďte na automatu, pak jedno Vámi vybrané řešení předejte k ohodnocení
vyučujícím. Předání úlohy k hodnocení učitelem se provede tlačítkem
"Předat vyučujícímu" u zvoleného řešení. Vyučující bude hodnotit pouze
jedno Vaše řešení, vyučující nezačně hodnotit dokud mu úlohu nepčředáte.
Dokud není úloha ohodnocena jak automatem tak i učitelem, nejsou
přidělené žádné body (jsou zobrazována pouze dílčí hodnocení v
procentech).</td>
</tr>
</tbody>
</table>
