
import commander from 'commander';

commander.program.command('java <inDir> <outDir> <package>')
        .description('quick generate pb java')
        .usage("java <inDir> <outDir> <package>")
        .action(function (inDir: string, outDir: string, packageName: string) {

        });


commander.program.parse(process.argv);